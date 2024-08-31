
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <getopt.h>

#include "mediaPlayer.h"

#define STDIN   0
#include <termios.h>
static struct termios termios_new, termios_old;
static int canonical_set;
#define GET_KEY_TIMEOUT_US 100000 // 100 millisec

#define MAX_PATH_LEN 4096 // ffmpeg MAX_URI_SIZE
#define MAX_URI_LISTS 10
#define NOPTS_VALUE 0x8000000000000000LL

/* globals */
static MediaPlayer * gPlayer = nullptr;
static bool         init_done = false;
static bool         quit = false;
static bool         quit_by_eos = false;
static bool         rpt = false;

static bool         playing = false;
static char        *s_path = NULL;
static uint64_t     duration, ptime, mtime;

static bool         verbose = false;
static int          start_time = 0;

static char         newuri[MAX_PATH_LEN];
static char        *uri_list[MAX_URI_LISTS];
static int          num_list = 0;
static int          cur_list = 0;

static char         *dumpfile = NULL;

/* functions */
int setup(int argc, char *argv[]);
int teardown(void);

static void commandline_help()
{
        fprintf(stdout, "\n============== Available Commands ===============\n");
        fprintf(stdout, "\t'q' - Quit\n");
        fprintf(stdout, "\t'h' - Help\n");
        fprintf(stdout, "\t'r' - Repeat\n");
        fprintf(stdout, "\t' ' - Pause\n");
        fprintf(stdout, "\t'i' - Print information\n");
        fprintf(stdout, "\n=================================================\n");
}

static void show_usages(char **argv)
{
        fprintf(stdout, "Usage:\n");
        fprintf(stdout, "\t%s /path/filename [Options] \n", argv[0]);
        fprintf(stdout, "\t%s file:///path/filename [Options]\n", argv[0]);
        fprintf(stdout, "\t%s url [Options]\n", argv[0]);
        fprintf(stdout, "\n");
        fprintf(stdout, "[Options]\n");
        fprintf(stdout, "\t --verbose,-v :\n");
        fprintf(stdout, "\t --starttime,-s <secs> : medai start position <sec>\n");
}

static const struct option long_options[]=
{
        {"verbose", 0, NULL, 'v'},
        {"help", 0, NULL, 'h'},
        {"starttime", 1, NULL, 's'},
        {NULL, 0, NULL, 0}
};

static void inputSignalCallbackHandler(int signum)
{
        fprintf( stdout, "Got signal...%d\n", signum);

        if (signum == SIGINT || signum == SIGTERM )
        {
                quit = true;

                /* do not repeat */
                rpt = false;
                cur_list = num_list;
        }
}

void keyboard_clear_canonical_mode()
{
        tcgetattr (STDIN, &termios_old);

        termios_new             = termios_old;
        termios_new.c_lflag    &= ~(ICANON | ECHO);
        termios_new.c_cc[VMIN]  = 1;
        termios_new.c_cc[VTIME] = 0;

        tcsetattr (STDIN, TCSANOW, &termios_new);

        canonical_set = 1;
}

void keyboard_set_canonical_mode()
{
        if (canonical_set) {
                tcsetattr (STDIN, TCSANOW, &termios_old);
        }
}

static int keyavailable(unsigned int seconds)
{
        struct timeval  tv;
        fd_set          readfds;

        tv.tv_sec = seconds / (1000 * 1000);
        tv.tv_usec = seconds % (1000 * 1000);

        FD_ZERO(&readfds);
        FD_SET(STDIN, &readfds);

        return (select(STDIN+1, &readfds, NULL, NULL, &tv) > 0);
}

static unsigned int getkey ()
{
        unsigned int ch = 0xff;

        read(STDIN, &ch, sizeof(unsigned int));

        return ch;
}

void terminal_enable_echo()
{
        struct termios tio;
        if (tcgetattr(STDIN_FILENO, &tio) < 0) {
                return;
        }
        tio.c_lflag |= ECHO | ICANON;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &tio);
}

void terminal_disable_echo()
{
        struct termios tio;
        if (tcgetattr(STDIN_FILENO, &tio) < 0) {
                return;
        }
        tio.c_lflag &=  ~( ECHO | ICANON );
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &tio);
}

void terminal_get_int32(int32_t *data)
{
        uint32_t i = 0;
        char buffer[31];
        char key;

        if (data == NULL)
                return;

        try_again:
        buffer[0] = '\0';
        while (i < 31) {
                if (keyavailable(GET_KEY_TIMEOUT_US)) {
                        key = getkey();
                        fprintf(stdout, "%c", key); fflush(stdout); //echo
                        if (((key >= '0') && (key <= '9')) || (key == '-')) {
                                buffer[i++] = key;
                                buffer[i] = '\0';
                        }
                        if ((key == '\n') || (key == '$')) {
                                buffer[i] = '\0';
                                break;
                        }
                }
        }

        sscanf(buffer, "%d", data);

        if (i < 1) {
                fprintf(stderr, "you must enter a number\n");
                goto try_again;
        }
}

void terminal_get_string(char *buffer)
{
        if (buffer == NULL)
                return;

        terminal_enable_echo();
        scanf("%s", buffer);
        terminal_disable_echo();
}

#define KEY_COMMAND_HELP                  'h'
#define KEY_COMMAND_QUIT                  'q'
#define KEY_COMMAND_PLAY                  'p'
#define KEY_COMMAND_PAUSE                 ' '
#define KEY_COMMAND_PRINT_INFO            'i'

void process_command(char key)
{
    int input;

    switch(key)
    {
        case KEY_COMMAND_HELP:
            commandline_help();
            break;
        case KEY_COMMAND_QUIT:
            quit = true;
            break;
        case KEY_COMMAND_PLAY:
            gPlayer->resumePlay();
            break;
        case KEY_COMMAND_PAUSE:
            gPlayer->pausePlay();
            break;
        case KEY_COMMAND_PRINT_INFO:
            //analyze_streams();
            break;
        deafult:
            fprintf(stdout, "unknown command %d\n", key);
            break;
   }
}

int reset_uri_lists()
{
        int i;

        if (num_list)
        {
                for (i=0; i<num_list && i<MAX_URI_LISTS; i++)
                {
                        if (uri_list[i])
                        {
                                free(uri_list[i]);
                                uri_list[i] = NULL;
                        }
                }
        }
        else
        {
                for (i=0; i<MAX_URI_LISTS; i++)
                {
                        uri_list[i] = NULL;
                }

                cur_list = 0;
        }

        if (s_path)
        {
                free(s_path);
                s_path = NULL;
        }
}

int teardown(void)
{
	if (gPlayer) {
		gPlayer->deinit();
		delete gPlayer; 	   
	}

	init_done = false;

	return 0;
}

int main(int argc, char* argv[])
{
	int hh, mm, ss = 0, ss_old = 0;
	int count = 100;
	char **args = argv;
	char *uri= NULL;

	int ret = 0;
	int i, flag = 0;
	int64_t start_time_msec = 0;
	const char *extension = NULL;
	
	if(argc < 2)
	{
			show_usages(args);
			return 1;
	}

	fprintf(stdout, "Parse command line : ");
	
	while(1)
	{
			int opt;
	
			const char *const short_options = ":vhes:f:S";
	
			int option_index = 0;
	
			opt = getopt_long(argc, argv, short_options, long_options, &option_index);
	
			/* Detect the end of option */
			if (opt == -1)
			{
					break;
			}

			switch(opt)
			{
					case 0:
							/* If this option set a flag, do nothing else now. */
							if (long_options[option_index].flag != 0)
									break;
							fprintf (stdout, "option %s", long_options[option_index].name);
							if (optarg)
									printf (" with arg %s", optarg);
							printf ("\n");
							break;
					case 'v' :
							verbose = true;
							fprintf(stdout, "verbose=1 ");
							break;
					case 'h' :
							commandline_help();
							break;
					case 's' :
							start_time = strtoul(optarg, NULL, 10);
							fprintf(stdout, "start_time=%d[sec] ", start_time);
							break;
					case 'f' :
							dumpfile = strdup(optarg);
							if (dumpfile)
								fprintf(stdout, "dump_file %s", dumpfile);
							break;

					case '?' :
							 /* getopt_long already printed an error message. */
							break;
					default :
							show_usages(args);
							exit(1);
							break;
			}
	}
	
	fprintf(stdout, "\nInput URL lists = \n");
	
	if (optind < argc)
	{
			while(optind < argc && num_list < MAX_URI_LISTS)
			{
					uri = argv[optind++];
	
					if (uri)
					{
							uri_list[num_list] = strdup(uri);
					}
	
					fprintf(stdout, "\tURI[%d] : %s\n", num_list, uri_list[num_list]);
					num_list++;
			}
	}

	// Register signal and signal handler
	signal(SIGINT, inputSignalCallbackHandler);
	signal(SIGTERM, inputSignalCallbackHandler);
	
	keyboard_clear_canonical_mode();
	
	if (num_list)
	{
		s_path = strdup(uri_list[0]);
	}
	
	if (s_path == NULL)
	{
		goto exit_;
	}

	if (start_time)
	{
		start_time_msec = (uint64_t)start_time * 1000;
	}

	if (!gPlayer) {
		if (!dumpfile) {
			gPlayer = new MediaPlayer();
		}
		else {
			gPlayer = new MediaPlayer(dumpfile);
		}
		if (!gPlayer) {
			fprintf(stdout, "failed to create a player\n");
			goto exit_;
		}
	}

	ret = gPlayer->init((const char*)s_path, 0);
	if (ret) {
		fprintf(stdout, "MediaPlayer init() failed\n");
		goto exit_;
	}

	gPlayer->startPlay(start_time);

	while( quit == false && gPlayer->isEOS() == false)
	{
		uint64_t curr_time_msec = 0LL;

		duration = gPlayer->getDuration();
		ptime = gPlayer->getPlayerTime();
		mtime = gPlayer->getMediaTime();

		if (ptime < 0) {
			usleep(100000);
			fprintf(stdout, "Player not ready\n");
		}

		// isEOS
		curr_time_msec = ptime; //mtime
		if (count++ < 3)
		{
			ss_old = (int)curr_time_msec%60;
		}
		else {
			uint64_t duration_ = duration;
			
			curr_time_msec/=1000;
			hh=(int)(curr_time_msec/3600); mm=(int)(curr_time_msec%3600)/60; ss = (int)curr_time_msec%60;
			if (ss != ss_old)
			{
					char uri[MAX_PATH_LEN];
					ss_old = ss;
					fprintf(stderr, "%02d:%02d:%02d/", hh, mm, ss);
					duration_/=1000;
					hh=(int)(duration_/3600); mm=(int)((duration_%3600)/60); ss = (int)(duration_%60);
					fprintf(stderr, "%02d:%02d:%02d\n", hh, mm, ss);
			}
		}

		if(keyavailable(GET_KEY_TIMEOUT_US))
		{
				char key = '\0';
				key = getkey();
				process_command(key);
		}
	}


exit_:
	keyboard_set_canonical_mode();
	if( 0 != teardown() )
	{
		return 1;
	}

	reset_uri_lists();

	if(dumpfile) {
		free(dumpfile);
		dumpfile = nullptr;
	}

    return 0;	
}

