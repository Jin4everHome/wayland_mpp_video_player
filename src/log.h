/*
 * Copyright (C) 2020 JoveAI Innovation Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __LOG_H__
#define __LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifdef __cplusplus
};
#endif


#define _DEBUG_ENABLE

#define DEFAULT_LOG_LEVEL LOG_LEVEL_DEBUG
//#define DEFAULT_LOG_LEVEL LOG_LEVEL_VERBOSE

enum {
	LOG_LEVEL_NONE    = 0,
	LOG_LEVEL_ERROR   = 1,
	LOG_LEVEL_WARNING = 2,
	LOG_LEVEL_INFO    = 3,
	LOG_LEVEL_DEBUG   = 4,
	LOG_LEVEL_VERBOSE = 5,
};

#define level_to_string( x ) \
    (x == LOG_LEVEL_ERROR) ? "_ERR" : \
    (x == LOG_LEVEL_WARNING) ? "_WARN" : \
    (x == LOG_LEVEL_INFO) ? "INFO" : \
    (x == LOG_LEVEL_DEBUG)?  "_DBG" : \
    (x == LOG_LEVEL_VERBOSE)? "_DBG" : "" \

#define logging(level) (level <= DEFAULT_LOG_LEVEL)

#define dbg_print(level, fmt, ...) do { \
    if (level > LOG_LEVEL_NONE && logging(level)) { \
        fprintf(stdout, "[%s][%s:%d] " fmt , level_to_string(level), __func__, __LINE__, ##__VA_ARGS__); \
    } \
} while(0)

#define dbg_print_time(level, fmt, ...) do { \
    if (level > LOG_LEVEL_NONE && logging(level)) { \
		struct timeval tv; \
		struct tm *tm; \
		gettimeofday(&tv, NULL); \
		tm = localtime(&tv.tv_sec); \
		fprintf(stdout, "[_DBG][%02d-%02d-%0d.%06ld][%s:%d] " fmt , tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec, __func__, __LINE__, ##__VA_ARGS__); \
    } \
} while(0)

#ifdef _DEBUG_ENABLE
#define LOGE(fmt,...) dbg_print(LOG_LEVEL_ERROR, fmt, ## __VA_ARGS__)
#define LOGW(fmt,...) dbg_print(LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__)
#define LOGI(fmt,...) dbg_print(LOG_LEVEL_INFO, fmt,##__VA_ARGS__)
#define LOGD(fmt,...) dbg_print(LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define LOGV(fmt,...) dbg_print_time(LOG_LEVEL_VERBOSE, fmt, ##__VA_ARGS__)
#else
#define LOGE(fmt,...)
#define LOGW(fmt,...)
#define LOGI(fmt,...)
#define LOGD(fmt,...)
#define LOGV(fmt,...)
#endif

inline void hexDump (char *desc, void *addr, int len)
{
    int i;
    char buff[17];
    char *pc = (char*)addr;
    char data[256];

    int written = 0;

    // Output description if given.
    if (desc != NULL)
        LOGD("%s:\n", desc);

    if (len == 0) {
        LOGD("  ZERO LENGTH\n");
        return;
    }
    if (len < 0) {
        LOGD("  NEGATIVE LENGTH: %i\n",len);
        return;
    }

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0) {
                sprintf(data + written, "  %s\n", buff);
                LOGD ("%s", data);
                written = 0;
                memset(data, 0, sizeof(data));
            }

            // Output the offset.
            written += sprintf(data+written, "  %04x ", i);
        }

        // Now the hex code for the specific character.
        written += sprintf(data + written, " %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        written += sprintf (data+written, "   ", nullptr);
        i++;
    }

    // And print the final ASCII bit.
    sprintf(data+written, "  %s\n", buff);
    LOGD ("%s", data);
}

#endif // __LOG_H__
