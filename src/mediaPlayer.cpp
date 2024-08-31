
#include <functional>
#include <string>
#include <vector>

#include "system_time.h"
#include "mediaPlayer.h"
#include "media_util.h"
#include "log.h"

namespace {
int AV_EXTRACTOR_LOG_LEVEL = AV_LOG_WARNING;

#define CODEC_PROBE_DATA_LENGTH (10*1000*1000)
#define R_MAX_DELAY_SEC 10 // reconnect max delay
/* TCP read/write wait timeout -> expired -> reconnect */
#define AV_OPTION_TCP_POLL_TIMEOUT (7*1000*1000) // 7 sec
/* pthread JOIN timeout */
#define PTHREAD_JOIN_TIMEOUT 45 // seconds

#define DEBUG_ENABLE_DECODE 0
#define DEBUG_ENABLE_DECODE_EXTRA 0
#define DEBUG_ENABLE_RENDER 0
#define DEBUG_ENABLE_FLOW 0

#define DISABLE_REUSE_PENDING_PACKET 0

#define RENDER_MODE_WITH_TIMESTRAMPS      0
#define RENDER_MODE_WITHOUT_TIMESTAMPS    1
#define RENDER_MODE_INSTANT               2

#define ENABLE_MPP_EXT_API 0

/* Set valud amomg RENDER_XXX */
#define RENDER_MODE RENDER_MODE_WITH_TIMESTRAMPS

static int use_avcc_global_ = 0;
//define ENABLE_MOVE_OUTFRAME
int64_t debug_frame_duration = 0LL;

std::string createString(char* a)
{
	std::string s(a);
	return s;
}

#define CODEC_ALIGN(x, a)   (((x)+(a)-1)&~((a)-1))

MppCodingType AVCodec_to_MPPCodec(enum AVCodecID codec)
{
	switch(codec)
	{
		case AV_CODEC_ID_MPEG2VIDEO: return MPP_VIDEO_CodingMPEG2; /**< AKA: H.262 */
		case AV_CODEC_ID_H264:       return MPP_VIDEO_CodingAVC;   /**< H.264/AVC */
		case AV_CODEC_ID_MPEG4:      return MPP_VIDEO_CodingMPEG4; /**< MPEG-4 */
		case AV_CODEC_ID_WMV1:
		case AV_CODEC_ID_WMV2:
		case AV_CODEC_ID_WMV3:       return MPP_VIDEO_CodingWMV;   /**< Windows Media Video (WMV1,WMV2,WMV3)*/
		case AV_CODEC_ID_VC1:        return MPP_VIDEO_CodingVC1;   /**< Windows Media Video (WMV1,WMV2,WMV3)*/
		case AV_CODEC_ID_HEVC:       return MPP_VIDEO_CodingHEVC;  /**< H.265/HEVC */
		//case AV_CODEC_ID_VP9:        return MPP_VIDEO_CodingVP9;   /**< VP9 */
		case AV_CODEC_ID_AVS:        return MPP_VIDEO_CodingAVS;   
		case AV_CODEC_ID_FLV1:       return MPP_VIDEO_CodingFLV1;
		case AV_CODEC_ID_VP9:        /*RK3288 Cannot support*/
		case AV_CODEC_ID_MPEG1VIDEO:
		default:                     return MPP_VIDEO_CodingUnused;
	}

	return MPP_VIDEO_CodingUnused;
}

const char* mppFrameFormatToString(MppFrameFormat format)
{

	switch(format) {
		case MPP_FMT_YUV420SP:
			return "MPP_FMT_YUV420SP";
		/*
		 * A rockchip specific pixel format, without gap between pixel aganist
		 * the P010_10LE/P010_10BE
		 */
		case MPP_FMT_YUV420SP_10BIT:
			return "MPP_FMT_YUV420SP_10BIT";
		case MPP_FMT_YUV422SP: /* YYYY... UVUV... (NV16)	*/
			return "MPP_FMT_YUV422SP";
		case MPP_FMT_YUV422SP_10BIT	: 	///< Not part of ABI
			return "MPP_FMT_YUV422SP_10BIT";
		case MPP_FMT_YUV420P: /* YYYY... U...V...  (I420) */
			return "MPP_FMT_YUV420P";
		case MPP_FMT_YUV420SP_VU: /* YYYY... VUVUVU... (NV21) */
			return "MPP_FMT_YUV420SP_VU";
		case MPP_FMT_YUV422P: /* YYYY... UU...VV...(422P) */
			return "MPP_FMT_YUV422P ";
		case MPP_FMT_YUV422SP_VU: /* YYYY... VUVUVU... (NV61) */
			return "MPP_FMT_YUV422SP_VU";
		case MPP_FMT_YUV422_YUYV: /* YUYVYUYV... (YUY2)		*/
			return "MPP_FMT_YUV422_YUYV";
		case MPP_FMT_YUV422_YVYU: /* YVYUYVYU... (YVY2)		*/
			return "MPP_FMT_YUV422_YVYU";
		case MPP_FMT_YUV422_UYVY: /* UYVYUYVY... (UYVY)		*/
			return "MPP_FMT_YUV422_UYVY";
		case MPP_FMT_YUV422_VYUY: /* VYUYVYUY... (VYUY)		*/
			return "MPP_FMT_YUV422_VYUY";
		case MPP_FMT_YUV400: /* YYYY...					*/
			return "MPP_FMT_YUV400";
		case MPP_FMT_YUV440SP: /* YYYY... UVUV...			*/
			return "MPP_FMT_YUV440SP";
		case MPP_FMT_YUV411SP: /* YYYY... UV...			*/
			return "MPP_FMT_YUV411SP";
		case MPP_FMT_YUV444SP: /* YYYY... UVUVUVUV...		*/
			return "MPP_FMT_YUV444SP";
		case MPP_FMT_YUV444P: /* YYYY... UUUU... VVVV...	*/
			return "MPP_FMT_YUV444P";
		case MPP_FMT_YUV_BUTT:
			return "MPP_FMT_YUV_BUTT";
		case MPP_FMT_RGB565: /* 16-bit RGB				*/
			return "MPP_FMT_RGB565";
		case MPP_FMT_BGR565: /* 16-bit RGB				*/
			return "MPP_FMT_BGR565";
		case MPP_FMT_RGB555: /* 15-bit RGB				*/
			return "MPP_FMT_RGB555";
		case MPP_FMT_BGR555: /* 15-bit RGB				*/
			return "MPP_FMT_BGR555";
		case MPP_FMT_RGB444: /* 12-bit RGB				*/
			return "MPP_FMT_RGB444";
		case MPP_FMT_BGR444: /* 12-bit RGB				*/
			return "MPP_FMT_BGR444";
		case MPP_FMT_RGB888: /* 24-bit RGB				*/
			return "MPP_FMT_RGB888";
		case MPP_FMT_BGR888: /* 24-bit RGB				*/
			return "MPP_FMT_BGR888";
		case MPP_FMT_RGB101010: /* 30-bit RGB				*/
			return "MPP_FMT_RGB101010";
		case MPP_FMT_BGR101010: /* 30-bit RGB				*/
			return "MPP_FMT_BGR101010";
		case MPP_FMT_ARGB8888: /* 32-bit RGB				*/
			return "MPP_FMT_ARGB8888";
		case MPP_FMT_ABGR8888: /* 32-bit RGB				*/
			return "MPP_FMT_ABGR8888";
		case MPP_FMT_BGRA8888: /* 32-bit RGB				*/
			return "MPP_FMT_BGRA8888";
		case MPP_FMT_RGBA8888: /* 32-bit RGB				*/
			return "MPP_FMT_RGBA8888";
		case MPP_FMT_RGB_BUTT:
			return "MPP_FMT_RGB_BUTT";
		default:
			break;
	}

	return "MPP_FMT_UNKNOWN";
}

} // namespace

int avInterruptCallback(void *context)
{
	MediaPlayer* player = static_cast<MediaPlayer*>(context);

	if (!player) {
		LOGE("Found No context allocated\n");
		if (!player->isInitDone())
		{
			usleep(1000);
			return 0;
		}

		if (!player->isWorkerActive() && player->isInitDone())
		{
			/* let ffmpeg send EOF */
			//if (player->isEOF() == false) {
			//	LOGD("Interrupt Callback at inactive state :  force EOF\n");
			//}
			//player->setEOF();
			return 1;
		}

		// TODO: HLS/DASH Live, please refer to jmplayer
		return 0;
	}

	// TODO:
	return 0; // player->interruptCallback();
}

MediaPlayer::MediaPlayer()
    :
    mCtx(NULL),
    mApi(NULL),
    mPkt(NULL),
    mBuffer(NULL),
    mFrmGrp(NULL),
    mDev(NULL)
{

}

MediaPlayer::MediaPlayer(const char* dumpfile)
	:
    mCtx(NULL),
    mApi(NULL),
    mPkt(NULL),
    mBuffer(NULL),
    mFrmGrp(NULL),
    mDev(NULL)
{
	dumpfile_ = createString((char*)dumpfile);
}

MediaPlayer::~MediaPlayer()
{
	deinit();
}

int MediaPlayer::init(const char *uri, int flags)
{
	AVFormatContext *av_fmt_ctx = nullptr;
	AVCodecContext *dec_ctx = nullptr;

	int video_stream_idx = -1;
	int audio_stream_idx = -1;
	AVDictionary *options = nullptr;	
	char probesize[100];
	int64_t duration;
	int ret;

	if (!uri) {
		LOGE("Invalid null point src paramter\n");
		return -1;
	}

	url_ = createString((char*)uri);

	if (!dumpfile_.empty()) {
		dumpfp_ = fopen(dumpfile_.c_str(), "w+b");
		if (dumpfp_) {
			LOGD("Open output dump file %s\n", dumpfile_.c_str());
		}
		else {
			LOGE("Cannot open output dump file %s\n", dumpfile_.c_str());
		}

		dumpCnt_ = 500;
	}

	LOGI("FFMPEG avformat version = 0x%x\n", avformat_version());
	LOGI("FFMPEG avcodec version = 0x%x\n", avcodec_version());

	//av_register_all();	//ffmpeg4.04.0
	avformat_network_init();

	av_fmt_ctx = avformat_alloc_context();
	if (!av_fmt_ctx) {
		//LOGE("Could not allocate context.\n");
		goto err1;
	}

	sprintf(probesize, "%d", CODEC_PROBE_DATA_LENGTH);
	av_dict_set(&options, "probesize", probesize, 0);

	av_dict_set_int(&options, "reconnect", 1, 0);
	av_dict_set_int(&options, "reconnect_delay_max", R_MAX_DELAY_SEC, 0);
	av_dict_set_int(&options, "rw_timeout", 3000000, 0); // TODO: side effect ???
	av_dict_set_int(&options, "timeout" , AV_OPTION_TCP_POLL_TIMEOUT, 0); // TODO: side effect ??

	/* AV log level set */
	av_log_set_level(AV_EXTRACTOR_LOG_LEVEL);


	/* should allocate callback before avformat_open_input for non hls stream */
	av_fmt_ctx->interrupt_callback.opaque	= this;
	av_fmt_ctx->interrupt_callback.callback = avInterruptCallback;

	if((ret = avformat_open_input(&av_fmt_ctx, url_.c_str(), nullptr, &options)) < 0) {
		LOGE("Could not open source file %s (ret= %d / 0x%x)\n", url_.c_str(), ret, ret); //, av_err2str(ret));

		if (ret == AVERROR_HTTP_NOT_FOUND || ret == -ENOENT)
		{
		}
		else if (ret == AVERROR_INVALIDDATA)
		{
		}
		else if (ret == AVERROR_DEMUXER_NOT_FOUND ||
				 ret == AVERROR_DECODER_NOT_FOUND)
		{
		}
		else if (ret == AVERROR_HTTP_UNAUTHORIZED ||
				 ret == AVERROR_HTTP_FORBIDDEN ||
				 ret == AVERROR_HTTP_SERVER_ERROR ||
				 ret == AVERROR_HTTP_BAD_REQUEST ||
				 ret == AVERROR_HTTP_OTHER_4XX)
		{

		}

		goto err1;
	}


	/* retrieve stream information */
	if(avformat_find_stream_info(av_fmt_ctx, nullptr) < 0)
	{
		LOGE("Could not find stream information\n");
		ret = -1;
		goto err1;
	}
	
	duration = av_fmt_ctx->duration;
	duration_msec_ = duration * 1000LL / AV_TIME_BASE;

	LOGD("duration = %lld(0x%llx)\n", duration, duration);
	LOGD("start time = %lld(%lld ms)\n", av_fmt_ctx->start_time, av_fmt_ctx->start_time*1000LL/AV_TIME_BASE);
	LOGD("nb_streams = %d\n", av_fmt_ctx->nb_streams);	

	start_offset_ = av_fmt_ctx->start_time;

	for(int i=0; i<av_fmt_ctx->nb_streams; i++) {
		if(av_fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
			av_fmt_ctx->streams[i]->discard = AVDISCARD_ALL;
		}
		else if (av_fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
			MppCodingType mpp_codec = AVCodec_to_MPPCodec(av_fmt_ctx->streams[i]->codecpar->codec_id);

			ret = mpp_check_support_format(MPP_CTX_DEC, mpp_codec);

			//if (mpp_codec != MPP_VIDEO_CodingUnused) {
			if (ret == MPP_OK) {
				int stream_idx = av_fmt_ctx->streams[i]->index;
				video_stream_idx_ = openCodecContext(&stream_idx, &dec_ctx, av_fmt_ctx, false);
				if (video_stream_idx_ != stream_idx) {
					LOGE("Unable to open codec index=%d(ret=%d)\n", stream_idx, video_stream_idx_);
					goto err1;
				}

				LOGI("Found VIDEO[%d] = %d @ start %lld(timebase num=%d, den=%d)\n",
					i,
					av_fmt_ctx->streams[i]->index,
					av_fmt_ctx->streams[i]->start_time,
					av_fmt_ctx->streams[i]->time_base.num,
					av_fmt_ctx->streams[i]->time_base.den);

				LOGD("VIDEO Stream[%d] extradata %d\n", stream_idx, dec_ctx->extradata_size);
				if (dec_ctx->extradata && (dec_ctx->extradata_size > 0)) {
					int codec_id = dec_ctx->codec_id;

					if (codec_id == AV_CODEC_ID_H264 ||
						codec_id == AV_CODEC_ID_HEVC ||
						codec_id == AV_CODEC_ID_MPEG4 ) {
						int header_size = 0;

						if (use_avcc_global_ == 1) {
							memcpy(vid_header_, dec_ctx->extradata, dec_ctx->extradata_size);
							vid_header_size_ = header_size = dec_ctx->extradata_size;
						}
						else {
							header_size = fill_header_video(dec_ctx, stream_idx);
						}

						if (header_size < 0) {
							// TODO:
							LOGE("Fill header failed...\n");
							goto err2;
						}

						if (header_size == 0) {
							LOGE("No header size found\n");
							goto err2;
						}

						LOGD("Codec configured...\n");

						is_codec_cofig_required_ = true;
					}
				}

				av_stream_ = av_fmt_ctx->streams[i];
				av_vid_dec_ctx_ = dec_ctx;
				av_fmt_ctx_ = av_fmt_ctx;
				mCodecId = mpp_codec;
				break;
			}
			else {
				av_fmt_ctx->streams[i]->discard = AVDISCARD_ALL;
			}
		}
		else if(av_fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_SUBTITLE) {
			av_fmt_ctx->streams[i]->discard = AVDISCARD_ALL;
		}
	}

	if (!av_vid_dec_ctx_) {
		LOGE("Unable to init decoder\n");
		goto err1;
	}

	initialize();
	
	mediaTimeProvider_.reset(new MediaTimeImpl(start_offset_));
	mediaTimeHandle_ = mediaTimeProvider_.get();
	
	//mediaTimeProvider_.reset(new MediaTimeImpl(start_offset_));
	//mediaTimeHandle_ = mediaTimeProvider_.get();
	start_time_ = 0;
	
	// create data thread;
	init_done_ = true;	

	return 0;

err2:
	if (dec_ctx) {
		avcodec_free_context(&dec_ctx);
		dec_ctx = nullptr;
	}

err1:
	if (av_fmt_ctx)
	{
		if(av_fmt_ctx->iformat)
			avformat_close_input(&av_fmt_ctx);
		avformat_free_context(av_fmt_ctx);
		av_fmt_ctx = nullptr;
	}

	if (videoStreamInfo_) {
		delete videoStreamInfo_;
	}

	avformat_network_deinit();

	return -1;
}

int MediaPlayer::deinit()
{
	// join the thead..
	LOGI("Player existing!!!");
	if (exiting_ || exitted_) {
		return 0;
	}

	exiting_ = true;
	worker_active_ = false;

	if (mediaTimeHandle_) {
		mediaTimeHandle_->Pause();
		paused_ = true;
	}

	if(ThreadIsValid(dataThread_)) {
		ThreadTimedJoin(dataThread_, nullptr, PTHREAD_JOIN_TIMEOUT);
		dataThread_ = kThreadInvalid;
	}

	if(ThreadIsValid(decoderThread_)) {
		ThreadTimedJoin(decoderThread_, nullptr, PTHREAD_JOIN_TIMEOUT);
		decoderThread_ = kThreadInvalid;
	}

	if(ThreadIsValid(renderThread_)) {
		ThreadTimedJoin(renderThread_, nullptr, PTHREAD_JOIN_TIMEOUT);
		renderThread_ = kThreadInvalid;
	}

	/* explicitly release */
	if (mediaTimeHandle_) {
		mediaTimeProvider_.reset();
		mediaTimeHandle_ = nullptr;
	}

	if (packetQueue_) {
		packetQueue_->clear();
		delete packetQueue_;
		packetQueue_ = nullptr;
	}

	mpp_video_frames_.flush();

	if (av_fmt_ctx_)
	{
		if (av_fmt_ctx_->iformat) {
			avformat_close_input(&av_fmt_ctx_);
		}
		avformat_free_context(av_fmt_ctx_);
		av_fmt_ctx_ = nullptr;
	}

	avformat_network_deinit();

	finalize();

	if (dumpfp_) {
		fclose(dumpfp_);
		dumpfp_ = nullptr;
	}

	init_done_ = false;
	exitted_ = true;

	LOGI("Player destroyed...\n");

	return 0;
}

int MediaPlayer::startPlay(int64_t start_time)
{
	int ret = 0;

	if (init_done_ == false) {
		LOGI("Player is not initialzied");
		return -1;
	}

	start_time = start_time*1000;
	if (start_time > 0 /*&& !isUDP_*/) {
		// TODO: seek is not implemented yet
	}

	packetQueue_ = new PacketQueue(0);
	if (!packetQueue_) {
		LOGE("Unable to allocate input queue\n");
		return -1;
	}

	worker_active_ = true;
	if (!ThreadIsValid(dataThread_)) {
		dataThread_ = ThreadCreate(
			0,
			kThreadPriorityNormal,
			0,
			true,
			"data_thread",
			&MediaPlayer::dataThreadEntryPoint, this);

		if (!ThreadIsValid(dataThread_)) {
			// TODO: event error callback;
			LOGE("Unable to create data receive thread\n");
			worker_active_ = false;
			goto err_;
		}
	}

	/* Create Decoder Thread */
	if (!ThreadIsValid(decoderThread_)) {
		decoderThread_ = ThreadCreate(0,
			kThreadPriorityNormal,
			(int32_t)80000000,
			true,
			"video_decoder",
			&MediaPlayer::decoderThreadEntryPoint,
			this);
		if (!ThreadIsValid(decoderThread_)) {
			LOGE("Unable to crate decode thread\n");
			exiting_ = true;
			return -1;
		}
	}

	/* Create Decoder Thread */
	if (!ThreadIsValid(renderThread_)) {
		renderThread_ = ThreadCreate(0,
			kThreadPriorityNormal,
			(int32_t)80000000,
			true,
			"video_renderer",
			&MediaPlayer::renderThreadEntryPoint,
			this);
		if (!ThreadIsValid(renderThread_)) {
			LOGE("Unable to crate renderer thread\n");
			exiting_ = true;
			return -1;
		}
	}

	if (mediaTimeProvider_) {
		mediaTimeHandle_->SetPlaybackRate(1.0, true);
		/* start with pause */
		mediaTimeHandle_->Pause();
	}

err_:
	// TODO: 

	return 0;
}

int MediaPlayer::pausePlay()
{
	LOGI("Player paused!!!");
	if (init_done_ == false) {
		LOGI("Player is not initialzied");
		return -1;
	}

	if (mediaTimeHandle_)
		mediaTimeHandle_->Pause();

	paused_ = true;

	return 0;
}

int MediaPlayer::resumePlay()
{

	LOGI("Player resumed!!!");

	if (init_done_ == false) {
		LOGI("Player is not initialzied");
		return -1;
	}

	if (mediaTimeHandle_)
		mediaTimeHandle_->Play();

	paused_ = false;
	return 0;
}

int MediaPlayer::seek(int64_t seek_to_secs, int flag)
{
	LOGW("SEEK is not implemented\n");
	return 0;
}

int64_t MediaPlayer::getDuration()
{
	return duration_msec_;
}

int64_t MediaPlayer::getPlayerTime()
{
	int media_time;
	
	if (!mediaTimeHandle_) {
		LOGE("MediaTime provider is not initialized\n");
		return -1;
	}

	media_time = mediaTimeHandle_->GetMediaTime();

	if (media_time < 0) {
		media_time = 0;
	}
	else {
		media_time = media_time/1000;
	}

	return media_time;
}

int64_t MediaPlayer::getMediaTime()
{
	static int64_t last_report_time = 0;
	int64_t time = lastVideoTimestamp_/1000;

	if (time > 0 && time >= last_report_time) {
		last_report_time = time;
	}

	return last_report_time;
}

bool MediaPlayer::isEOS()
{
	return isEOSPlayed();
}

#define PKT_SIZE (1024*1024)

int MediaPlayer::initialize()
{
	int ret;
	int codec_id = av_vid_dec_ctx_->codec_id;
	// MPP_FMT_YUV420P, MPP_FMT_YUV420SP, MPP_FMT_ARGB8888
	MppFrameFormat output_fmt = MPP_FMT_YUV420SP;

	int x, y, i;
	uint32_t need_split = 1;
	MpiCmd mpi_cmd = MPP_CMD_BASE;
	MppParam param = NULL;
	MppCodingType type = MPP_VIDEO_CodingUnused;

	mSrcW = av_vid_dec_ctx_->width;
	mSrcH = av_vid_dec_ctx_->height;
	mDstW = 1920;
	mDstH = 1080;

	mFrameDispInfo.x= 0;
	mFrameDispInfo.y= 0;
	mFrameDispInfo.width=  av_vid_dec_ctx_->width;
	mFrameDispInfo.height= av_vid_dec_ctx_->height;
	mFrameDispInfo.strideW= CODEC_ALIGN(mFrameDispInfo.width, 16); // Check value 16 per codec and format
	mFrameDispInfo.strideH= CODEC_ALIGN(mFrameDispInfo.height, 16);
	mFrameDispInfo.format = MPP_FMT_YUV420SP;

	mOutDispInfo.x= 0;
	mOutDispInfo.y= 0;
	mOutDispInfo.width= 1920;
	mOutDispInfo.height= 1080;
	mOutDispInfo.strideW= CODEC_ALIGN(mFrameDispInfo.width, 16); // Check value 16 per codec and format
	mOutDispInfo.strideH= CODEC_ALIGN(mFrameDispInfo.height, 16);
	mOutDispInfo.format = (int)output_fmt;

	mPktBuf = new char[PKT_SIZE];
	if (!mPktBuf) {
		LOGE("Unable to allocate memory for Input Packet\n");
		return -1;
	}

	ret = mpp_packet_init(&mPkt, mPktBuf, PKT_SIZE);
	if (ret) {
		LOGE("Failed to mpp_packet_init\n");
		return -1;
	}

	// Create mpp context
	ret = mpp_create(&mCtx, &mApi);
	if (ret != MPP_OK) {
		LOGE("failed to call mpp_create (ret=%d)\n", ret);
		return -1;
	}

#if 0
	/* TODO: What this isNOTE: MPP fast mode must be applied before mpp_init()  */
	//MPP_DEC_SET_ENABLE_FAST_PLAY
	int fast_mode = 1;
	ret = mApi->control (mCtx, MPP_DEC_SET_PARSER_FAST_MODE, &fast_mode);
	//ret = mApi->control (mCtx, MPP_DEC_SET_ENABLE_FAST_PLAY,  &fast_mode);

	int paramS32 = 1;
	//ret = mApi->control(mCtx, MPP_DEC_SET_PRESENT_TIME_ORDER, &paramS32);
	if (ret != MPP_OK) {
	LOGE("Failed to set block timeout on MPI (code = %d).\n", ret);
	}
#endif

	type = mCodecId;

	ret = mpp_init(mCtx, MPP_CTX_DEC, type);
	if (ret != MPP_OK) {
		LOGE("failed to exec mpp_init.\n");
		return -1;
	}
#if 0
	#define RECEIVE_FRAME_TIMEOUT 100

	int64_t paramS64 = RECEIVE_FRAME_TIMEOUT;
	ret = mApi->control(mCtx, MPP_SET_OUTPUT_TIMEOUT, &paramS64);
	if (ret != MPP_OK) {
	LOGE("Failed to set block timeout on MPI (code = %d).\n", ret);
	}
	//MPP_DEC_SET_PRESENT_TIME_ORDER
#endif


#if USE_WAYLAND_RENDERER
	mEGLDevice = std::unique_ptr<EGLDisplayOut>(new EGLDisplayOut(24));
	if (!mEGLDevice) {
		LOGE("EGL display renderer is not created\n");
		return -1;
	}
#else
	mDev = create_sp_dev();
	if (!mDev) {
		LOGE("failed to exec create_sp_dev.\n");
		return -1;
	}

	ret = initialize_screens(mDev);
	if (ret != 0) {
		LOGE("failed to exec initialize_screens.\n");
		return -1;
	}

	mPlanes = (sp_plane **)calloc(mDev->num_planes, sizeof(*mPlanes));
	if (!mPlanes) {
		LOGE("failed to calloc mPlanes.\n");
		return -1;
	}

	for (i=0; i<mDev->num_crtcs; i++) {
		sp_crtc *tmp = &mDev->crtcs[i];
		if (tmp->valid) {
			mCrtc = tmp;
			break;
		}
	}

	if (i==mDev->num_crtcs || !mCrtc) {
		LOGE("failed to resolve DRM crtc\n");
		return -1;
	}

	for (i = 0; i < mCrtc->num_planes; i++) {
		mPlanes[i] = get_sp_plane(mDev, mCrtc);
		if (is_supported_format(mPlanes[i], DRM_FORMAT_NV12)) {
			mTestPlane = mPlanes[i];
		}
	}

	LOGE("mCRTC W:H=%d:%d\n", mCrtc->crtc->mode.hdisplay, mCrtc->crtc->mode.vdisplay);
#endif

	/* initialize output drm rendering frame */
	for(int i=0; i<NUM_OF_RENDER_FRAMES; i++) {
		mRenderFrame[i] = nullptr;
	}

	if (!mTestPlane) {
		LOGE("failed to get mTestPlane.\n");
		return -1;
	}

	return 0;
}


int MediaPlayer::finalize()
{
	if (mPkt) {
		mpp_packet_deinit(&mPkt);
		mPkt = NULL;
	}

	if (mCtx) {
		Reset();
		mpp_destroy(mCtx);
		mCtx = NULL;
	}

	if (mPktBuf) {
		delete(mPktBuf);
		mPktBuf = NULL;
	}

	if (mBuffer) {
		mpp_buffer_put(mBuffer);
		mBuffer = NULL;
	}

	if (mFrmGrp) {
		for (int i=0; i<NUM_OF_RENDER_FRAMES; i++) {
			if (mRenderFrame[i]) {
				mpp_frame_deinit(&mRenderFrame[i]);
			}
		}
		mpp_buffer_group_put(mFrmGrp);
		mFrmGrp = NULL;
	}

	if (mExtFrmGrp) {
		mpp_buffer_group_put(mExtFrmGrp);
		mExtFrmGrp = NULL;
	}

#if	USE_WAYLAND_RENDERER
	if (mEGLDevice) {
		mEGLDevice.reset();
	}
#endif

	if (mDev) {
		destroy_sp_dev(mDev);
		mDev = nullptr;
	}

	return 0;
}

void MediaPlayer::Decode(AVPacket *packet)
{
}

void MediaPlayer::Reset()
{
	if (mCtx && mApi)
		mApi->reset(mCtx);
}

int MediaPlayer::GetMaxDecodeRequests()
{
	return 1;
}

bool MediaPlayer::isEOSWritten()
{
	return eos_written_;
}

bool MediaPlayer::isEOSPlayed()
{
	return eos_consumed_;
}

bool MediaPlayer::isWritable()
{
	if (!packetQueue_)
		return false;

	if (packetQueue_->getSize() > 200) {
		return false;
	}

	return true;
}

bool MediaPlayer::isFirstFrameRendered()
{
	return first_frame_rendered_;
}

int MediaPlayer::queuePacket(AVPacket *packet)
{
	PacketQueue *queue = nullptr;
	int64_t timestamp = 0LL;
	//AVPacket orig_pkt;
	int64_t orig_pts;
	int64_t orig_flags;

	queue = packetQueue_;

	if (!queue) {
		LOGE("Found no queue(%p)\n", queue);
		return -1;
	}

	//orig_pkt = *packet;
	orig_pts = packet->pts;
	orig_flags = packet->flags;

	if (packet->pts < 0 && packet->pts != AV_NOPTS_VALUE) {
		LOGW("Unexpected video[%d] packet pts %lld ( < 0 ) received\n", packet->stream_index, packet->pts);
		av_packet_unref(packet);
		return 0;
	}

	if (!strcmp((const char *)packet->data, "EOS")) {
		packet->pts = AV_NOPTS_VALUE;
	}

	if (packet->pts == AV_NOPTS_VALUE && !strcmp((const char *)packet->data, "EOS")) {

		if (lastPacketPts_>0) {
			packet->pts = lastPacketPts_;
		}
		else {
			/* First Packet */
			packet->pts = av_rescale_q(start_offset_, AV_TIME_BASE_Q, av_stream_->time_base);
			firstPacketPts_ = packet->pts;
			LOGD("Set First packet pts %lld (from start_offset_ %lld\n", firstPacketPts_, start_offset_);

			if (firstPacketPts_ < 0) {
				/* First Packet */
				packet->pts = av_rescale_q(start_offset_, AV_TIME_BASE_Q, av_stream_->time_base);
				firstPacketPts_ = packet->pts;
				LOGD("Set First packet pts %lld (from start_offset_ %lld\n", firstPacketPts_, start_offset_);
			}
			else {
				packet->pts = 0;
				LOGD("PTS Unknown ---- Need to debugging\n");
			}
		}
	}
	else if (!strcmp((const char *)packet->data, "EOS")) {
		if (packet->pts < 0) {
			LOGD("Adjust Packet PTS %lld -> 0\n", packet->pts);
			packet->pts = 0;
		}
	}

	if (firstPacketPts_ < 0) {
		firstPacketPts_ = packet->pts;
	}

	if (lastPacketPts_ < packet->pts) {
		lastPacketPts_ = packet->pts;
	}

	if (queue->push_back(packet)) {
		LOGE("Fail to queue a packet %lld\n", packet->pts);
		av_packet_unref(packet);
		return -1;
	}

	return 1;
}

int MediaPlayer::fill_header_video(AVCodecContext *dec_ctx, int stream_idx)
{
	uint8_t* vid_header = nullptr;

	if(!dec_ctx->extradata || !dec_ctx->extradata_size) return 0;

	if (dec_ctx->extradata_size > VID_HEADER_SIZE) {
		LOGE("Extradata is out of bound (MAX %d < %d)\n", VID_HEADER_SIZE, dec_ctx->extradata_size);
	}

	if(dec_ctx->codec_id == AV_CODEC_ID_H264)
	{
		//hexDump("CODEC_DATA_ORG", dec_ctx->extradata, dec_ctx->extradata_size);
		vid_header_size_ = MediaUtil::h264_add_header(dec_ctx, vid_header_);
		LOGD("EXTRA DATA H264 = %d\n", vid_header_size_);
		//hexDump("CODEC_DATA_REV", vid_header_, vid_header_size_);

		return vid_header_size_;
	}
	else if(dec_ctx->codec_id == AV_CODEC_ID_HEVC)
	{
		vid_header_size_ = MediaUtil::hevc_add_header(dec_ctx, vid_header_);
		return vid_header_size_;
	}
	else if(dec_ctx->codec_id == AV_CODEC_ID_MPEG4)
	{
		vid_header_size_ = MediaUtil::codec_add_header(dec_ctx, vid_header_);
		return vid_header_size_;
	}

	return 0;
}

int MediaPlayer::openCodecContext(int* stream_idx, AVCodecContext **dec_ctx, AVFormatContext *fmt_ctx, bool best_effort)
{
	int ret, stream_index;
	AVStream *st;
	AVCodec *dec = nullptr;
	AVDictionary *opts = nullptr;
	AVCodecParameters * codec_para = nullptr;
	const char* codec_name = nullptr;

	if (!fmt_ctx || !stream_idx) {
		LOGE("Invalid null point parameter\n");
		return -1;
	}

	if (*stream_idx < 0) {
		ret =  av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
	}
	else {
		if (best_effort) {
			int index = *stream_idx;

			if (index < fmt_ctx->nb_streams) {
				ret = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, index, -1, nullptr, 0);
			}
			else {
				ret = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
			}
		}
		else {
			ret = *stream_idx;
		}
	}

	if (ret < 0) {
		LOGE("Could not find %s stream\n", av_get_media_type_string(AVMEDIA_TYPE_VIDEO));
		return ret;
	}

	stream_index = ret;
	st = fmt_ctx->streams[stream_index];
	codec_para = fmt_ctx->streams[stream_index]->codecpar;
	if (!codec_para || !st) {
		LOGE("Found no stream or codec parameter\n");
		return -1;
	}

	/* find decoder for the stream */
	LOGD("Trying to find a decoder for codec_id = %d\n", codec_para->codec_id);
	dec = avcodec_find_decoder(st->codecpar->codec_id);
	if(!dec)
	{
		LOGE("Failed to find %s codec\n", av_get_media_type_string(AVMEDIA_TYPE_VIDEO));
		return AVERROR(EINVAL);
	}

	/* Allocate a codec context for the decoder */
	*dec_ctx = avcodec_alloc_context3(dec);
	if(!*dec_ctx)
	{
		LOGE("Failed to allocate the %s codec context\n", av_get_media_type_string(AVMEDIA_TYPE_VIDEO));
		return AVERROR(ENOMEM);
	}

	/* Copy codec parameters from input stream to output codec context */
	if((ret = avcodec_parameters_to_context(*dec_ctx, st->codecpar)) < 0)
	{
		LOGE("Failed to copy %s codec parameters to decoder context\n", av_get_media_type_string(AVMEDIA_TYPE_VIDEO));
		return ret;
	}

	/* Init the decoders, with or without reference counting */
	int refcount = 0;

	av_dict_set(&opts, "refcounted_frames", refcount ? "1" : "0", 0);
	int retry = 10;
	while (retry--)
	{
		if ((ret = avcodec_open2(*dec_ctx, dec, &opts)) < 0) {
			usleep(1000);
			continue;
		}
		else {
			break;
		}
	}

	if (ret < 0) {
		LOGE("Failed to open %s codec\n", av_get_media_type_string(AVMEDIA_TYPE_VIDEO));
		if (dec_ctx) {
				avcodec_free_context(dec_ctx);
				dec_ctx = nullptr;
		}

		return ret;
	}

	*stream_idx = stream_index;

	LOGI("Find %s codec %s(stream idx = %d)\n", av_get_media_type_string(AVMEDIA_TYPE_VIDEO), (*dec_ctx)->codec->name, stream_index);

	return ret;
}

MppPacket MediaPlayer::getMppPacket(void* data, size_t size, int64_t pts)
{
	MppPacket mpkt = NULL;
	mpp_packet_init (&mpkt, data, size);

	if (mpkt) {
		if (pts >= 0) {
			mpp_packet_set_pts(mpkt, pts);
		}
	}
	
	return mpkt;  	
}

int MediaPlayer::sendMppPacket(MppPacket packet, int timeout_ms)
{
	int interval_ms = 2;
	MPP_RET ret;

	do {
		ret =  mApi->decode_put_packet (mCtx, packet);
		if (ret == MPP_OK) {
			mpp_packet_deinit (&packet);
			return 0;
		}

	  usleep(interval_ms * 1000);
	  timeout_ms -= interval_ms;
	} while (timeout_ms > 0);

	return -1;
}

int MediaPlayer::sendCodecData(void *data, size_t size)
{
	int ret = -1;
	MppPacket mpkt = nullptr;

	mpp_packet_init (&mpkt, (void *)data, size);
	if (mpkt) {
		mpp_packet_set_extra_data (mpkt);
		ret =  mApi->decode_put_packet (mCtx, mpkt);
		if (ret != MPP_OK) {
			LOGE("Failed to send codec specific data\n");
		}
		mpp_packet_deinit (&mpkt);
	}
	else {
		LOGE("Unable mpp_packet_init()\n");
	}

	return ret;
}

int MediaPlayer::sendEosData(int timeout_ms)
{
	int interval_ms = 2;
	MppPacket mpkt = nullptr;
	MPP_RET ret;

	mpp_packet_init (&mpkt, NULL, 0);
	if (mpkt) {
		mpp_packet_set_eos(mpkt);
		do {
			ret =  mApi->decode_put_packet (mCtx, mpkt);
			if (ret == MPP_OK) {
				mpp_packet_deinit (&mpkt);
				return 0;
			}
			usleep(interval_ms * 1000);
			timeout_ms -= interval_ms;
		} while (timeout_ms > 0);

		LOGE("Send EOS Packet Timeout\n");
		mpp_packet_deinit (&mpkt);
	}
	else {
		LOGE("Unable mpp_packet_init()\n");
	}

	return -1;
}

int MediaPlayer::setExternalBuffer(int size, int count)
{
#define BUFFER_MANAGER_TEST 1

#if BUFFER_MANAGER_TEST
#define VERIFYBUF
#endif
	std::vector<MppBuffer> tmp_bufs;
#ifdef VERIFYBUF
	std::vector<MppBuffer> verify_bufs;
#endif

	MppBufferType bufType = MPP_BUFFER_TYPE_DRM; // MPP_BUFFER_TYPE_DRM
	int ret = 0;

	if (!mFrmGrp) {
		mpp_buffer_group_get_internal (&mFrmGrp, bufType);
		if (!mFrmGrp) {
			LOGE("Unable to get frame group\n");
			return -1;
		}
	}

	if (!mExtFrmGrp) {
		mpp_buffer_group_get_external (&mExtFrmGrp, bufType);
	}

	/* Create DRM buffer from rockchip mpp internally 	*/
	for (int i=0; i<count; i++) {
		MppBuffer tmp_buf = nullptr;
		if (mpp_buffer_get(mFrmGrp, &tmp_buf, size)) {
			LOGE("Cannot allocate buffer %d \n", i);
			goto error_;
		}
		tmp_bufs.push_back(tmp_buf);
	}

	for (int i=0; i<count; i++) {
		MppBuffer mpp_buf;
		MppBufferInfo commit;

		mpp_buf = (MppBuffer *)tmp_bufs.front();
		tmp_bufs.erase(tmp_bufs.begin());
		if (!mpp_buf) {
			LOGE("Found no mpp buffer in the container\n");
			goto error_;
		}

		mpp_buffer_set_index(mpp_buf, i);
		mpp_buffer_info_get(mpp_buf, &commit);

		if (mpp_buffer_commit(mExtFrmGrp, &commit)) {
			LOGE("Commit %d buffer failed\n");
			mpp_buffer_put(mpp_buf);
			ret = -1;
			break;
		}

		mpp_buffer_put(mpp_buf);

#if BUFFER_MANAGER_TEST
		if (mpp_buffer_get(mExtFrmGrp, &mpp_buf, size)) {
			LOGE("Cannot get mpp buffer from External Buffer Group\n");
			ret = -1;
			break;
		}
		else {
			LOGD("External Get Buffer[%d] %p, fd=%d, vaddr=%p\n",
			    i,
			    mpp_buf,
			    mpp_buffer_get_fd(mpp_buf),
			    mpp_buffer_get_ptr(mpp_buf));
#ifdef VERIFYBUF
			verify_bufs.push_back(mpp_buf);
#else
			mpp_buffer_put(mpp_buf);
#endif
			/* make another memory manager here */
		}
#endif
	}

	if (ret) {
		goto error_;
	}

#ifdef VERIFYBUF
	// Erase all even numbers
	if (1) {
		int cnt = count;
		while (verify_bufs.size() > 0 || cnt) {
			MppBuffer mpp_buf;
			mpp_buf = (MppBuffer *)verify_bufs.front();
			verify_bufs.erase(verify_bufs.begin());
			mpp_buffer_put(mpp_buf);
			cnt--;
		}
	}
#endif

	ret = mApi->control (mCtx, MPP_DEC_SET_EXT_BUF_GROUP, mExtFrmGrp);
	if (ret) {
		LOGE("%p set buffer group failed ret %d\n", mCtx, ret);
		goto error_;
	}

#if 0
	// No for external buffer group//
	ret = mpp_buffer_group_limit_config(mExtFrmGrp, size, count);
	if (ret) {
		LOGE("Failed to set buffer group limit (code = %d)\n", ret);
		goto error_;
	}
#endif
	mpp_buffer_group_put(mFrmGrp);
	mFrmGrp = nullptr;

	mUseExteranlBuffer = true;
	return 0;

error_:
	if (tmp_bufs.size() > 0) {
		tmp_bufs.clear();
	}

	if (mFrmGrp) {
		mpp_buffer_group_put(mFrmGrp);
		mFrmGrp = nullptr;
	}

	if (mExtFrmGrp) {
		mpp_buffer_group_put(mExtFrmGrp);
		mExtFrmGrp = nullptr;
	}

	return -1;
}

void MediaPlayer::getFitScreenCordination(const MppFrame frame, bool isRotate, uint32_t& x, uint32_t& y, uint32_t& width, uint32_t& height)
{
#define BYTE_ALIGN(in, a)   (((in)+(a)-1)&~((a)-1))

	bool isDownscale = false;

	uint32_t dispWidth  = 1920;
	uint32_t dispHeight = 1080;

	double scalefactor = 0;
	double scaleWidth  = 0;
	double scaleHeight = 0;

	uint32_t frameWidth   = mpp_frame_get_width(frame);
	uint32_t frameHeight  = mpp_frame_get_height(frame);
	uint32_t frameWStride = mpp_frame_get_hor_stride(frame);
	uint32_t frameHStride = mpp_frame_get_ver_stride(frame);

	uint32_t virtualFrameWidth   = frameWidth;
	uint32_t virtualFrameHeight  = frameHeight;
	uint32_t virtualFrameWStride = frameWStride;
	uint32_t virtualFrameHStride = frameHStride;

	if (isRotate) {
		virtualFrameWidth   = frameHeight;
		virtualFrameHeight  = frameWidth;
		virtualFrameWStride = frameHStride;
		virtualFrameHStride = frameWStride;
	}

	if (dispWidth < virtualFrameWidth || dispHeight < virtualFrameHeight) {
		isDownscale = true;
	}

	scaleWidth	= (double)dispWidth/virtualFrameWidth;
	scaleHeight   = (double)dispHeight/virtualFrameHeight;

	if (scaleWidth <= scaleHeight) {
		scalefactor = scaleWidth;
	}
	else {
		scalefactor = scaleHeight;
	}

	double scaledWidth  = virtualFrameWidth  * scalefactor;
	double scaledHeight = virtualFrameHeight * scalefactor;
	width  = (int)scaledWidth;
	height = (int)scaledHeight;

	width = BYTE_ALIGN(width, 4);
	if (width > dispWidth) {
		width = dispWidth;
	}

	height= BYTE_ALIGN(height, 4);

	if (height > dispHeight) {
		height = dispHeight;
	}

	if (width != dispWidth) {
		uint32_t dist = dispWidth - width;
		x = dist / 2;
	}
	else {
		x = 0;
	}

	if (height != dispHeight) {
		uint32_t dist = dispHeight - height;
		y = dist / 2;
	}
	else {
		y = 0;
	}
}


int MediaPlayer::decodeVideoPacket(/* TODO */)
{
	int ret = 0;
	bool input_buffer_already_written = false;
	void* data = nullptr;
	int size = 0;
	bool isEOS = false;
	int64_t timestamp = 0;
	int64_t pts = 0LL;
	int has_input = 0;
	int got_packet = 0; // to be removed...
	AVPacket *avPacket = nullptr;

	int pendingCnt = 0;

	AVPacket *packet = nullptr;
	AVStream *stream = nullptr;
	int is_keyframe = 0;
	enum InputType input_type = INPUT_TYPE_STREAM;

	MppFrame _srcFrm;
	MppFrame* srcFrm = &_srcFrm;
	static int64_t last_decode_time = 0;

	if (flushing_) {
		usleep(1000);
		return 0;
	}

	//if (packetQueue_->empty()) {
	//	usleep(1000);
	//	return 0;
	//}

	stream = av_stream_;
	if (!stream) {
		LOGE("Invalid stream index %d\n", video_stream_idx_);
		return -1;
	}

	if (!eos_written_) {
		if (is_codec_cofig_required_) {
			if (vid_header_size_ > 0) {
	 			data = vid_header_;
				size = vid_header_size_;

				ret = sendCodecData(data, size);
				if (ret) {
					// TODO: loop
					LOGD("Failed to decode extradata (size=%d, ret=%d)\n", size, ret);
				}
				else {
					is_codec_cofig_required_ = false;
					//decoding_frames_++;
				}
			}
			else {
				is_codec_cofig_required_ = false;
			}
		}

		if (!first_packet_received_) {
			if (!packetQueue_->empty()) {
				/* Don't use avpacket here, will be unref without pop */
				AVPacket *pkt_tmp = packetQueue_->front();
				// WORKAROUND: Test stream has no key frame found.
				//first_packet_received_ = true;
				if (pkt_tmp->flags & AV_PKT_FLAG_KEY) {
					LOGE("First Packet received ...\n");
					first_packet_received_ = true;
				}
				else if(pkt_tmp == &packetQueue_->eos_pkt) {
					first_packet_received_ = true;
					is_codec_cofig_required_ = false;
					avPacket = pkt_tmp;
					LOGD("Not found keyframe and EOS Packet received...\n");
				}
				else {
					ret = packetQueue_->pop_front(&avPacket_);
					if (ret < 0) {
						LOGE("No avPacket found\n");
						usleep(1000);
						return -1;
					}

					//LOGD("[DEBUG] Not found keyframe : drop packet timestamp=%lld\n", av_rescale_q(avPacket_->pts, stream->time_base, AV_TIME_BASE_Q));
					av_packet_unref(avPacket_);
					return 0;
				}
			}
			else {
				usleep(1000);
				return 0;
			}
		}

		int64_t curr_media_time = mediaTimeHandle_->GetMediaTime();

		// Debug only
		if (0) {
			int usedslots;
			ret = mApi->control(mCtx, MPP_DEC_GET_VPUMEM_USED_COUNT, &usedslots);
			if (ret != MPP_OK) {
				LOGE("Failed to get decoder used slots (code = %d).\n", ret);
				return ret;
			}
			// we get the available slots in decoder

			// Why allways 0:
			ret = mApi->control(mCtx, MPP_DEC_GET_STREAM_COUNT, &usedslots);
			if (ret != MPP_OK) {
				LOGE("Failed to get decoder used slots (code = %d).\n", ret);
				return ret;
			}
			LOGD("Used Stream = %d\n", usedslots);
		}

		if ((decoding_frames_ - (rendered_frames_ + dropped_frames_) > 15) && (decoded_frames_>0)) {
		//if (debug_frame_duration > 0 && ((curr_media_time - last_decode_time) < debug_frame_duration - 1000) && decoding_frames_ > 10) { /* Slow Input Test : enable RENDER_MODE_WITHOUT_TIMESTAMPS */
			// skip
			has_input = 0;
			usleep(1000);
		}else if (PendingPacketInput_.valid) {
			input_type = PendingPacketInput_.type;
			if (input_type == INPUT_TYPE_STREAM) {
				avPacket = PendingPacketInput_.avPacket;
			}

			PendingPacketInput_.valid = false;
			has_input = 1;
		}
		else if(!packetQueue_->empty()) {
			ret = packetQueue_->pop_front(&avPacket_);
			if (ret < 0) {
				LOGE("No avPacket found\n");
				usleep(1000);
				return -1;
			}

			avPacket = avPacket_;

			if (!avPacket->data) {
				LOGD("Got avpacket buf null data, size=%d, queued=%d, org=%p, queue(%p), queue->index=%d\n",
				avPacket->size,
				packetQueue_->getSize(),
				avPacket_->data,
				packetQueue_,
				packetQueue_->getStreamId());
				av_packet_unref(avPacket);
				return 0;
			}

			if (avPacket == &packetQueue_->eos_pkt) {
				input_type = INPUT_TYPE_EOS;
			}
			else {
				input_type = INPUT_TYPE_STREAM;
			}
			
			has_input = 1;
 		}
 	}

	if (has_input) {
		if (input_type == INPUT_TYPE_STREAM) {
			if (avPacket) {
				MppPacket packet = nullptr;
				if (use_avcc_global_ == 0) {
					if (av_vid_dec_ctx_->codec_id == AV_CODEC_ID_H264) {
						MediaUtil::h264_update_frame_header(avPacket->data, avPacket->size);
					}
					else if(av_vid_dec_ctx_->codec_id == AV_CODEC_ID_HEVC)
					{
						MediaUtil::hevc_update_frame_header(avPacket->data, avPacket->size);
					}
				}

				data = avPacket->data;
				size = avPacket->size;
				pts = avPacket->pts;

				/* Normalize */
				if (pts != AV_NOPTS_VALUE && pts >= 0) {
					timestamp = av_rescale_q(pts, stream->time_base, AV_TIME_BASE_Q);
				}
				else {
					if (lastPacketTimeStamp_ > 0) {
						timestamp = lastPacketTimeStamp_;
					}
					else {
						timestamp = 0;
					}
				}

				packet = getMppPacket(data, size, timestamp);
				if (!packet) {
					// TODO: reuse and error handling
					LOGE("Unable to get a MppPacket\n");
					return -1;
				}

				ret = sendMppPacket(packet, 2000);
				if (ret) {
					if (DEBUG_ENABLE_DECODE_EXTRA) {
						LOGD("Decoding pending reason=%d, cnt=%d, decoding=%d, decoded=%d\n", ret, ++pendingCnt, decoding_frames_, decoded_frames_);
#if ENABLE_MPP_EXT_API
						if (mExtFrmGrp) {
							LOGD("External BufferGroup usage = %d, unused = %d, used = %d \n", mpp_buffer_group_usage(mExtFrmGrp), mpp_buffer_group_unused(mExtFrmGrp), mpp_buffer_group_used(mExtFrmGrp));
						}
						if (mFrmGrp) {
							LOGD("Internal BufferGroup usage = %d, unused = %d, used = %d \n", mpp_buffer_group_usage(mFrmGrp), mpp_buffer_group_unused(mFrmGrp), mpp_buffer_group_used(mExtFrmGrp));
						}
#endif
					}

					if (DISABLE_REUSE_PENDING_PACKET) {
						usleep(1000);
						if (avPacket) {
							av_packet_unref(avPacket);
							avPacket = nullptr;
						}
						
						pendingCnt = 0;
						PendingPacketInput_.valid = false;
						usleep(1000);
					}
					else {
						PendingPacketInput_.type = input_type;
						PendingPacketInput_.handle = nullptr; // reserved
						PendingPacketInput_.id = 0; 		  // reserved
						PendingPacketInput_.avPacket = avPacket;
						PendingPacketInput_.valid = true;
						usleep(3000);
					}
				}
				else {
					if (firstPacketTimeStamp_ < 0) {
						firstPacketTimeStamp_ = timestamp;
						mediaTimeHandle_->Seek(timestamp, 0);
						mediaTimeHandle_->Play();
						LOGI("First frame decoding done (mediaTime %lld/%lld)\n", firstPacketTimeStamp_, mediaTimeHandle_->GetMediaTime());
					}
					
					char *buf = (char*)data;
					if (DEBUG_ENABLE_DECODE) {
						LOGD("Decoding Packet %p (size=%d, pts=%lld 0x%02x%02x%02x%02x %02x\n", data, size, timestamp, buf[0], buf[1], buf[2], buf[3], buf[4]);
					}

					if (avPacket) {
						av_packet_unref(avPacket);
						avPacket = nullptr;
					}
					
					last_decode_time = mediaTimeHandle_->GetMediaTime();
					
					decoding_frames_++;
					pendingCnt = 0;
					PendingPacketInput_.valid = false;

					if (lastPacketTimeStamp_ < timestamp) {
						lastPacketTimeStamp_ = timestamp;
	 				}
				}
			}
 			else {
				/* should not happen */
				LOGE("Found no avPacket...\n");
				usleep(10000);
				return -1;
 			}
 		}
		else if (input_type == INPUT_TYPE_EOS) {
			ret = sendEosData(1000);
			if (ret) {
				LOGE("Send EOS data failed\n");
				if (DEBUG_ENABLE_DECODE_EXTRA) {
					LOGD("EOS Decoding pending reason=%d, cnt=%d\n", ret, ++pendingCnt);
				}

				if (DISABLE_REUSE_PENDING_PACKET) {
					pendingCnt = 0;
					PendingPacketInput_.valid = false;
				}
				else {
					PendingPacketInput_.type = input_type;
					PendingPacketInput_.handle = nullptr; // reserved
					PendingPacketInput_.id = 0; 		  // reserved
					PendingPacketInput_.avPacket = nullptr;
					PendingPacketInput_.valid = true;
					usleep(3000);
				}
			}
			else {
				LOGI("EOS Packet written\n");
				eos_written_ = true;
				decoding_frames_++;
				PendingPacketInput_.valid = false;
			}
		}
		else {
			LOGE("Invalid video input type %d\n", input_type);
		}
	}

	return 0;
}

int MediaPlayer::renderOneDrmFrame(MppFrame frame)
{
	sp_bo *bo;
	uint32_t handles[4], pitches[4], offsets[4];
	uint32_t width, height;
	uint32_t widthS, heightS;
	uint32_t offset_x, offset_y;
	int frm_size, ret, fd, err;
	int drm_pixel_format = DRM_FORMAT_NV12;

	if (!frame) {
		LOGD("No frame to render\n");
		return 0;
	}

	switch(mpp_frame_get_fmt (frame))
	{
		case MPP_FMT_YUV420P:
			drm_pixel_format = DRM_FORMAT_YUV420;
			break;
		case MPP_FMT_RGB888:
			drm_pixel_format = DRM_FORMAT_RGB888;
			break;
		case MPP_FMT_YUV420SP_10BIT:
			drm_pixel_format = DRM_FORMAT_YUV420;
			break;
		default:
			drm_pixel_format = DRM_FORMAT_NV12;
	}

	err = mpp_frame_get_errinfo(frame) | mpp_frame_get_discard(frame);
	if (err) {
		LOGE("get err info %d discard %d,go back.\n",
				mpp_frame_get_errinfo(frame),
				mpp_frame_get_discard(frame));
		return -1;
	}

	/* DEBUG Dump */
	if (dumpfp_) {
		if (rendered_frames_ + dropped_frames_ > 800 && rendered_frames_ + dropped_frames_ < 1000) {
			dumpFrameToFile(frame, dumpfp_);
		}
	}

	width = mpp_frame_get_width(frame);
	height = mpp_frame_get_height(frame);
	widthS = mpp_frame_get_hor_stride(frame);
	heightS = mpp_frame_get_ver_stride(frame);
	offset_x = mpp_frame_get_offset_x(frame);
	offset_y = mpp_frame_get_offset_y(frame);

	frm_size = widthS * heightS * 3 / 2;
	fd = mpp_buffer_get_fd(mpp_frame_get_buffer(frame));

	bo = (struct sp_bo *)calloc(1, sizeof(struct sp_bo));
	if (!bo) {
		LOGE("failed to calloc bo.\n");
		return -2;
	}

	drmPrimeFDToHandle(mDev->fd, fd, &bo->handle);
	bo->dev = mDev;
	bo->width = width;
	bo->height = height;
	bo->depth = 16;
	bo->bpp = 32;
	bo->format = drm_pixel_format;
	bo->flags = 0;

	handles[0] = bo->handle;
	pitches[0] = widthS;
	offsets[0] = 0;

	if (drm_pixel_format == DRM_FORMAT_NV12 || drm_pixel_format == DRM_FORMAT_NV16) {
		handles[1] = bo->handle;
		pitches[1] = widthS;
		offsets[1] = widthS * heightS;
	}

	ret = drmModeAddFB2(mDev->fd, bo->width, bo->height,
	                    bo->format, handles, pitches, offsets,
	                    &bo->fb_id, bo->flags);

	if (ret != 0) {
		LOGE("failed to exec drmModeAddFb2.\n");
		return -1;
	}

	getFitScreenCordination(frame, false, offset_x, offset_y, width, height);

	ret = drmModeSetPlane(mDev->fd, mTestPlane->plane->plane_id,
	                      mCrtc->crtc->crtc_id, 
	                      bo->fb_id,
	                      0,
	                      offset_x, offset_y,
	                      width, //mCrtc->crtc->mode.hdisplay,
	                      height, //mCrtc->crtc->mode.vdisplay,
	                      0<<16, 0<<16,
	                      bo->width << 16,
	                      bo->height << 16);
	if (ret) {
		LOGE("failed to exec drmModeSetPlane.\n");
		return -1;
	}

	if (mTestPlane->bo) {
		if (mTestPlane->bo->fb_id) {
			ret = drmModeRmFB(mDev->fd, mTestPlane->bo->fb_id);
			if (ret) {
				LOGE("failed to exec drmModeRmFB.\n");
			}
		}

		if (mTestPlane->bo->handle) {
			struct drm_gem_close req = {
					.handle = mTestPlane->bo->handle,
			};
			drmIoctl(bo->dev->fd, DRM_IOCTL_GEM_CLOSE, &req);
		}
		free(mTestPlane->bo);
	}
	mTestPlane->bo = bo;

	return 0;
}

int MediaPlayer::renderFrame()
{
	int ret = 0;
	mediaTime ref_time;
	int64_t timestamp;
	const int64_t thresholdTime = 5000;
	MppFrame frame = nullptr;
	int64_t debug_start_time = 0LL, debug_end_time = 0LL;

	if (paused_) {
		if (DEBUG_ENABLE_FLOW) {
			LOGD("Render : paused_\n");
		}
		usleep(1000);
		return 0;
	}

	if (eos_consumed_) {
		return 0;
	}

	if (mpp_video_frames_.empty() || eos_consumed_) {
		if (DEBUG_ENABLE_FLOW) {
			LOGD("Render : return (frames=%d (empty=%d), eos_consumed_=%d, eos_written_=%d)\n", mpp_video_frames_.size(), mpp_video_frames_.empty(), eos_consumed_, eos_written_);
		}
		usleep(1000);
		return 0;
	}

	frame = mpp_video_frames_.front();
	if (frame) {
		timestamp = mpp_frame_get_pts(frame);
	}
	else {
		LOGE("Found no frame(CRITICAL) empty(%d), size(%d)\n", mpp_video_frames_.empty(), mpp_video_frames_.size());
		usleep(1000);
		return -1;
	}

	if (mpp_video_frames_.size() > 0) {
		MppFrame frame = mpp_video_frames_.front();
		if (!frame ) {
			LOGE("Found no frame(CRITICAL) empty(%d), size(%d)\n", mpp_video_frames_.empty(), mpp_video_frames_.size());
			return 0;
		}

		int IsEos = mpp_frame_get_eos(frame);
		timestamp = mpp_frame_get_pts(frame);

		if (!IsEos) {
			mediaTime media_time = mediaTimeHandle_->GetMediaTime(); // TODO:

			int64_t ealry_us = timestamp - media_time;

			if (RENDER_MODE == RENDER_MODE_WITHOUT_TIMESTAMPS) {
				if (lastVideoTimestamp_ < timestamp && timestamp >= 0) {
					int64_t duration = timestamp - lastVideoTimestamp_;
					
					if (duration != debug_frame_duration) {
						if (DEBUG_ENABLE_RENDER) {
							//LOGD("Frame duration changed from %lld -> %lld\n", debug_frame_duration, duration);
						}
						debug_frame_duration = duration;
					}
				
					lastVideoTimestamp_ = timestamp;
				}
#if USE_WAYLAND_RENDERER
				if (mEGLDevice) {
					mEGLDevice->Render(frame);
				}
#else
				renderOneDrmFrame(frame);
#endif
				rendered_frames_++;

				MppBuffer mbuf = mpp_frame_get_buffer (frame);
				if (mbuf) {
					if (DEBUG_ENABLE_RENDER) {
						LOGD("Video render : frame(%p) time=%lld, media_time=%lld, diff(f-m)=%lld, inteval=%lld, d:dd:r:q(%d:%d:%d:%d), fd=%d, ptr=%p\n",
							frame,
							timestamp,
							media_time,
							timestamp-media_time,
							debug_frame_duration,
							decoding_frames_,
							decoded_frames_,
							rendered_frames_ + dropped_frames_,
							mpp_video_frames_.size(),
							mpp_buffer_get_fd(mbuf),
							mpp_buffer_get_ptr(mbuf)
							// this API is not committed to MPP
							/*,mpp_buffer_get_ref_count(mbuf)*/);
					}
#ifdef ENABLE_MOVE_OUTFRAME
					mpp_buffer_put(mbuf);
#endif
				}

				mpp_video_frames_.pop_front();
				usleep(1000);
				ret = 1;
			}
			else {
				if (ealry_us < -30*1000) {
					/* Drop frame */
					if (DEBUG_ENABLE_RENDER) {
						LOGD("Drop frame timestamp = %lld, media_time=%lld\n", timestamp, media_time);
					}

					if (lastVideoTimestamp_ < timestamp && timestamp >= 0) {
						int64_t duration = timestamp - lastVideoTimestamp_;

						if (duration != debug_frame_duration) {
							if (DEBUG_ENABLE_RENDER) {
								//LOGD("Frame duration changed from %lld -> %lld\n", debug_frame_duration, duration);
							}
							debug_frame_duration = duration;
						}

						lastVideoTimestamp_ = timestamp;
					}

#if USE_WAYLAND_RENDERER
					if (mEGLDevice) {
						mEGLDevice->Render(frame);
					}
#else // USE_WAYLAND_RENDERER
					MppFrame RenderFrame = getRenderFrame(dropped_frames_ + rendered_frames_);
					renderOneDrmFrame(frame);
#endif // USE_WAYLAND_RENDERER
					MppBuffer mbuf = mpp_frame_get_buffer(frame);
					if (mbuf) {
						if (0 /*DEBUG_ENABLE_RENDER*/) {
							LOGD("MBUF(%p) : fd=%d, ptr=%p, size=%d\n", 
							 mbuf,
							 mpp_buffer_get_fd(mbuf),
							 mpp_buffer_get_ptr(mbuf),
							 mpp_buffer_get_size(mbuf));
						}
#ifdef ENABLE_MOVE_OUTFRAME
						mpp_buffer_put (mbuf);
#endif
					}

					mpp_video_frames_.pop_front();
					dropped_frames_++;
					ret = 0;
				}
				else if (ealry_us < 50 * 1000) {
					if (lastVideoTimestamp_ < timestamp && timestamp >= 0) {
						int64_t duration = timestamp - lastVideoTimestamp_;

						if (duration != debug_frame_duration) {
							if (DEBUG_ENABLE_RENDER) {
								//LOGD("Frame duration changed from %lld -> %lld\n", debug_frame_duration, duration);
							}
							debug_frame_duration = duration;
						}
						
						lastVideoTimestamp_ = timestamp;
					}

#if USE_WAYLAND_RENDERER
					if (mEGLDevice) {
						mEGLDevice->Render(frame);
					}
#else // USE_WAYLAND_RENDERER
					MppFrame RenderFrame = getRenderFrame(dropped_frames_ + rendered_frames_);

					renderOneDrmFrame(frame);
#endif //USE_WAYLAND_RENDERER
					MppBuffer mbuf = mpp_frame_get_buffer (frame);
					if (mbuf) {
						if (DEBUG_ENABLE_RENDER) {
							LOGD("Video render : frame(%p) time=%lld, media_time=%lld, diff(f-m)=%lld, inteval=%lld, d:dd:r:q(%d:%d:%d:%d), fd=%d, ptr=%p\n",
								frame,
								timestamp,
								media_time,
								timestamp-media_time,
								debug_frame_duration,
								decoding_frames_,
								decoded_frames_,
								rendered_frames_ + dropped_frames_,
								mpp_video_frames_.size(),
								mpp_buffer_get_fd(mbuf),
								mpp_buffer_get_ptr(mbuf)
								// this API is not committed to MPP
								/*,mpp_buffer_get_ref_count(mbuf)*/);
						}

#ifdef ENABLE_MOVE_OUTFRAME
						mpp_buffer_put(mbuf);
#endif
					}

					mpp_video_frames_.pop_front();
					rendered_frames_++;
					ret = 1;
				}
				else {
					usleep(1000);
					ret = 0;
				}
			}
		}
		else {
			LOGI("EOS Frame consumed\n");
			mpp_video_frames_.pop_front();
			eos_consumed_ = true;
		}
	}

	return ret;
}

void* MediaPlayer::dataThreadEntryPoint(void* context)
{
	if (!context)
		return nullptr;

	MediaPlayer* player = static_cast<MediaPlayer*>(context);
	player->dataThreadFunc();
	return nullptr;
}

void MediaPlayer::dataThreadFunc()
{
	int64_t current_timestamp;
	int64_t time_now;
	int64_t timestamp;

	AVPacket pkt1;
	AVPacket *packet = &pkt1;
	bool set_eos = false;
	bool wait_video_eos_set = false;
	int ret = 0;

	dataThreadRunning_ = true;

	while(worker_active_)
	{
		time_now = getSystemTimeNow()/1000; // milliseconds

		if (!init_done_) {
			usleep(1000);
			continue;
		}
		
		if (vid_eos_set_) {
			if (isEOSPlayed()) {
				vid_eos_set_ = false;
			}

			if (vid_eos_set_ == false) {
				LOGE("Player EOS reached\n");
				break;
			}

			usleep(1000);
			continue;
		}

		if (!isWritable()) {
			usleep(50000);
			continue;
		}

		if (!worker_active_) {
			break;
		}

		/* Mark packet read start time */
		packet_read_time_ = getSystemTimeNow();		

		if ((ret = av_read_frame(av_fmt_ctx_, packet)) < 0) {
			packetQueue_->eos_pkt.pts = AV_NOPTS_VALUE; // handle pts inside decoder
			queuePacket(&packetQueue_->eos_pkt);
			vid_eos_set_ = true;

			// TODO :
			if (av_fmt_ctx_ && av_fmt_ctx_->pb && av_fmt_ctx_->pb->error) {
				LOGE("Player : read frame failed %d/0x%x\n", av_fmt_ctx_->pb->error, av_fmt_ctx_->pb->error);
				break;
			}
			
			set_eos = true;
			continue;
		}

		packet_read_time_ = 0;		

		/* Is this a packet from the video stream? */
		if(packet->stream_index == video_stream_idx_ && av_vid_dec_ctx_) {
			ret = queuePacket(packet);
			if (ret < 0) {
				LOGE("Could not queue a input packet(FATAL)\n");
				// TODO: error report
				goto ERROR_;
			}
			else if (ret == 0) {
				// packet was discarded
			}
		}
		else {
			av_packet_unref(packet);
		}
	}

	LOGI("Player worker thread exit done.\n");
	dataThreadRunning_ = false;
	return;	

ERROR_:
	LOGI("Player worker thread exit done with error.\n");
	dataThreadRunning_ = false;
}

// static
void* MediaPlayer::decoderThreadEntryPoint(void* context)
{
	if (!context)
		return nullptr;

	MediaPlayer* decoder = static_cast<MediaPlayer*>(context);
	decoder->decoderThreadFunc();
	return nullptr;
}

void MediaPlayer::decoderThreadFunc()
{
	AVPacket packet;
	av_init_packet(&packet);
	avPacket_ = &packet;

	decoderThreadRunning_ = true;

	LOGI("Video decoder thread start...\n");
	while(!exiting_ && !reseting_)
	{
		bool has_input = false;
		int ret;

		if (flushing_) {
			usleep(1000);
			continue;
		}

		ret = decodeVideoPacket();
		if (ret < 0) {
			LOGE("Video decoding error (ret=%d)\n", ret);
			// TODO: do action.
		}
		else if (ret == 0) {
			usleep(1000);
		}
		else {
			usleep(1000);
		}
	}

	LOGI("Video decoder thread exit done...\n");
	decoderThreadRunning_ = false;
}

void* MediaPlayer::renderThreadEntryPoint(void *context)
{
	if (!context)
		return nullptr;

	MediaPlayer* renderer = static_cast<MediaPlayer*>(context);
	renderer->renderThreadFunc();
	return nullptr;
}

void MediaPlayer::renderThreadFunc()
{
	LOGI("Video Renderer thread start...\n");
	renderThreadRunning_ = true;
	while(!exiting_ && !reseting_)
	{
		int ret;

		if (paused_) {
			usleep(1000);
			continue;
		}

		if (flushing_) {
			usleep(1000);
			continue;
		}

		if (eos_consumed_) {
			break;
		}

		if (!mediaTimeHandle_) {
			LOGE("Found no mediaTimeProvider\n");
			usleep(1000);
			continue;
		}
		
		if (1 /*mpp_video_frames_.size() < 4*/) {

			RK_S32 get_frm = 0;
			RK_U32 frm_eos = 0;

			MppFrame _srcFrm;
			MppFrame* srcFrm = &_srcFrm;

			ret = mApi->decode_get_frame(mCtx, srcFrm);
			if (ret == MPP_ERR_TIMEOUT) {
				LOGD("decode_get_frame failed too much time.\n");
				usleep(1);
			}
			else if (*srcFrm) {
				if (mpp_frame_get_info_change(*srcFrm)) {
					ret = outputFormatChanged(*srcFrm);
					if (ret) {
						LOGE("[CRITICAL ERROR] Failed to call outputFormatChanged\n");
					}
					mpp_frame_deinit(srcFrm);
				} else if (mpp_frame_get_eos(*srcFrm)) {
					LOGI("EOS Frame received\n");
					eos_consumed_ = true;
					mpp_frame_deinit(srcFrm);
				} else if (mpp_frame_get_discard(*srcFrm)) {
					LOGE("[CRITICAL ERROR] Received a discard frame!!!\n");
					mpp_frame_deinit(srcFrm);
					usleep(1000);
				} else if (mpp_frame_get_errinfo(*srcFrm)) {
					LOGE("[CRITICAL ERROR] Received a errinfo frame!!!\n");
					mpp_frame_deinit(srcFrm);
					usleep(1000);
				} else {
					if (RENDER_MODE != RENDER_MODE_INSTANT) {
#if ENABLE_MPP_EXT_API
						if (mFrmGrp && !mUseExteranlBuffer) {
							static size_t max_usage = 0;
							size_t usage = mpp_buffer_group_usage(mFrmGrp);
						
							//LOGD("MAX_USAGE = %d\n", usage);
							if (usage > max_usage) {
								max_usage = usage;
							}

							// This API is not committed to MPP
							//size_t used = mpp_buffer_group_used(mFrmGrp);
							//LOGD("Used buffer = %d, usage= %d\n", used, usage);
						}
						else {
							static size_t max_usage = 0;
							size_t usage = mpp_buffer_group_usage(mExtFrmGrp);

							//LOGD("MAX_USAGE = %d\n", usage);
							if (usage > max_usage) {
								max_usage = usage;
							}

							// This API is not committed to MPP
							//size_t used = mpp_buffer_group_used(mFrmGrp);
							//LOGD("Used buffer = %d, usage= %d\n", used, usage);
						}
#endif

#ifdef ENABLE_MOVE_OUTFRAME
						MppFrame dstFrm= NULL;
						MppFrame *out = &dstFrm;
						int width  = mpp_frame_get_width(*srcFrm);
						int height =  mpp_frame_get_height(*srcFrm);
						int hor_stride = CODEC_ALIGN(width, 16);
						int ver_stride = CODEC_ALIGN(height, 16);

						mpp_frame_set_width(out, width);
						mpp_frame_set_height(out, height);
						mpp_frame_set_hor_stride(out, hor_stride);
						mpp_frame_set_ver_stride(out, ver_stride);
						mpp_frame_set_pts(out, mpp_frame_get_pts(*srcFrm));
						mpp_frame_set_eos(out, mpp_frame_get_eos(*srcFrm));
						mpp_frame_set_fmt(out, mpp_frame_get_fmt(*srcFrm));

						MppBuffer mbuf = mpp_frame_get_buffer(*srcFrm);

						mpp_frame_set_buffer(out, mbuf);
						mpp_buffer_inc_ref(mbuf);
						mpp_frame_deinit(srcFrm);
						mpp_video_frames_.push_back(out);
						decoded_frames_++;
#else
						mpp_video_frames_.push_back(*srcFrm);
						decoded_frames_++;
#endif
					}
					else {
#if USE_WAYLAND_RENDERER
						if (mEGLDevice) {
							mEGLDevice->Render(*srcFrm);
						}
#else
						renderOneDrmFrame(*srcFrm);
#endif
						decoded_frames_++;
						rendered_frames_++;
						int64_t timestamp = mpp_frame_get_pts(*srcFrm);

						if (lastVideoTimestamp_ < timestamp && timestamp >= 0) {
							int64_t duration = timestamp - lastVideoTimestamp_;
							
							if (duration != debug_frame_duration) {
								if (DEBUG_ENABLE_RENDER) {
									//LOGD("Frame duration changed from %lld -> %lld\n", debug_frame_duration, duration);
								}
								debug_frame_duration = duration;
							}

							lastVideoTimestamp_ = timestamp;
						}

						LOGD("Video render : frame(%p) time=%lld, d:dd:r(%d:%d:%d)\n",
							*srcFrm,
							mpp_frame_get_pts(*srcFrm),
							decoding_frames_,
							decoded_frames_,
							rendered_frames_);
						
						usleep(1000);
						mpp_frame_deinit(srcFrm);
					}
				}
			}
			else {
				//LOGD("No frame ret=%d\n", ret);
				usleep(1000);
			}
		}

		ret = renderFrame();
		if (ret <= 0) {
			usleep(1000);
		}
		else {
			usleep(1000);
		}
	}
	LOGI("Video Renderer thread exit done...\n");
	renderThreadRunning_ = false;
}


MppFrame MediaPlayer::getRenderFrame(int count)
{
	MppFrame frame = nullptr;
	int idx = count % NUM_OF_RENDER_FRAMES;

	if (mRenderFrame[idx]) {
		frame = mRenderFrame[idx];
	}
	else {
		LOGE("Found no container for rendering frame\n");
	}

	return frame;
}


int MediaPlayer::outputFormatChanged(MppFrame frame)
{
	int ret;
	RK_U32 width, height, hor_stride, ver_stride, buf_size;
	RK_U32 offset_x, offset_y;
	MppFrameFormat mpp_format;
	bool afbc;
	int num_out_frames = 24;

	if (!frame) {
		LOGE("[%s] Invalid null point parameter\n", __func__);
		return -1;
	}

	width = mpp_frame_get_width(frame);
	height = mpp_frame_get_height(frame);
	hor_stride = mpp_frame_get_hor_stride(frame);
	ver_stride = mpp_frame_get_ver_stride(frame);
	offset_x = mpp_frame_get_offset_x(frame);
	offset_y = mpp_frame_get_offset_y(frame);
	buf_size = mpp_frame_get_buf_size(frame);
	mpp_format = mpp_frame_get_fmt (frame);

	afbc = !!MPP_FRAME_FMT_IS_FBC (mpp_format);

	LOGI("decode_get_frame get info changed found.\n");
	LOGI("decoder require buffer(%d) w:h [%d:%d] stride [%d:%d], fromat %s \n",
		 buf_size, width, height, hor_stride, ver_stride, mppFrameFormatToString(mpp_format));

	offset_x = mpp_frame_get_offset_x (frame);
	offset_y = mpp_frame_get_offset_y (frame);

	mFrameDispInfo.x= (int)offset_x;
	mFrameDispInfo.y= (int)offset_y;
	mFrameDispInfo.width= (int)width;
	mFrameDispInfo.height= (int)height;
	mFrameDispInfo.strideW= (int)hor_stride;
	mFrameDispInfo.strideH= (int)ver_stride;
	mFrameDispInfo.format = (int)mpp_format;

	if (mUseExteranlBuffer == false) {
		if (nullptr == mFrmGrp) {
			/* If buffer group is not set create one and limit it */
			ret = mpp_buffer_group_get_internal(&mFrmGrp, MPP_BUFFER_TYPE_DRM);
			if (ret) {
				LOGE("%p get mpp buffer group failed ret %d\n", mCtx, ret);
				return -1;
			}

			/* Set buffer to mpp decoder */
			ret = mApi->control(mCtx, MPP_DEC_SET_EXT_BUF_GROUP, mFrmGrp);
			if (ret) {
				LOGE("%p set buffer group failed ret %d\n", mCtx, ret);
				return -1;
			}
		} else {
			/* If old buffer group exist clear it */
			ret = mpp_buffer_group_clear(mFrmGrp);
			if (ret) {
				LOGE("%p clear buffer group failed ret %d\n", mCtx, ret);
				return -1;
			}
		}

		/* TODO: Use limit config to limit buffer count to 24 with buf_size */
		if (1) {
			ret = mpp_buffer_group_limit_config(mFrmGrp, buf_size, num_out_frames);
			if (ret) {
				LOGE("%p limit buffer group failed ret %d\n", mCtx, ret);
				return -1;
			}
			else {
				LOGI("decoder total frame buffer %d\n", buf_size * num_out_frames);

			}
		}
	}
	else {
		int count = 0;

		/* The required buffer size caculation:
		 * hor_stride * ver_stride * 3 / 2 for pixel data
		 * hor_stride * ver_stride / 2 for extra info
		 * Total hor_stride * ver_stride * 2 will be enough
		 * But Pixel format is not yuv420sp, you should recalcurate its size
		 * For example if pixel format is 10bit, each frame buffer size would be increased by value ?
		 * So we just use the size from updated frame info here.
		 */
		//size = mFrameDispInfo.strideW * mOutDispInfo.strideH *2;

		/* For H.264/H.265 20+ buffers will be enough
		 * For other codec 10 buffers will be enough
		 */
		if (mCodecId == MPP_VIDEO_CodingAVC || mCodecId == MPP_VIDEO_CodingHEVC) {
			count = 24;
		}
		else {
			count = 12;
		}

		if (setExternalBuffer(buf_size, count)) {
			LOGE("Unable allocate external DRM buffer\n");
			return -1;
		}

		for (int i=0; i<NUM_OF_RENDER_FRAMES; i++) {
			if (mRenderFrame[i]) {
			#if 1
				mpp_frame_set_width(mRenderFrame[i], mpp_frame_get_width(frame));
				mpp_frame_set_height(mRenderFrame[i], mpp_frame_get_height(frame));
				mpp_frame_set_hor_stride(mRenderFrame[i], mpp_frame_get_hor_stride(frame));
				mpp_frame_set_ver_stride(mRenderFrame[i], mpp_frame_get_ver_stride(frame));
			#else
				mpp_frame_set_width(mRenderFrame, 1920);
				mpp_frame_set_height(mRenderFrame, 1080);
				mpp_frame_set_hor_stride(mRenderFrame, CODEC_ALIGN(1920, 16));
				mpp_frame_set_ver_stride(mRenderFrame, CODEC_ALIGN(1080, 16));
			#endif

				mpp_frame_set_offset_x(mRenderFrame[i], mpp_frame_get_offset_x(frame));
				mpp_frame_set_offset_y(mRenderFrame[i], mpp_frame_get_offset_y(frame));
				mpp_frame_set_fmt(mRenderFrame[i], mpp_frame_get_fmt(frame));
			}
		}
	}

	mApi->control(mCtx, MPP_DEC_SET_INFO_CHANGE_READY, nullptr);
#if USE_WAYLAND_RENDERER
	if (mEGLDevice) {
		mEGLDevice->initDisplay(1920, 1024, num_out_frames);
	}
#endif

	return 0;
}

void MediaPlayer::dumpFrameToFile(MppFrame frame, FILE *fp)
{
	RK_U32 width    = 0;
	RK_U32 height   = 0;
	RK_U32 h_stride = 0;
	RK_U32 v_stride = 0;
	MppFrameFormat fmt  = MPP_FMT_YUV420SP;
	MppBuffer buffer    = NULL;
	RK_U8 *base = NULL;

	if (NULL == fp || NULL == frame)
		return ;

	width    = mpp_frame_get_width(frame);
	height   = mpp_frame_get_height(frame);
	h_stride = mpp_frame_get_hor_stride(frame);
	v_stride = mpp_frame_get_ver_stride(frame);
	fmt      = mpp_frame_get_fmt(frame);
	buffer   = mpp_frame_get_buffer(frame);

	if (NULL == buffer)
		return ;

	base = (RK_U8 *)mpp_buffer_get_ptr(buffer);

	// TODO:
	fmt = MPP_FMT_YUV420P;

	switch (fmt) {
		case MPP_FMT_YUV422SP : {
		    /* YUV422SP -> YUV422P for better display */
		    RK_U32 i, j;
		    RK_U8 *base_y = base;
		    RK_U8 *base_c = base + h_stride * v_stride;
		    RK_U8 *tmp = (RK_U8*)malloc(h_stride * height * 2);
		    RK_U8 *tmp_u = tmp;
		    RK_U8 *tmp_v = tmp + width * height / 2;

		    for (i = 0; i < height; i++, base_y += h_stride)
		        fwrite(base_y, 1, width, fp);

		    for (i = 0; i < height; i++, base_c += h_stride) {
		        for (j = 0; j < width / 2; j++) {
		            tmp_u[j] = base_c[2 * j + 0];
		            tmp_v[j] = base_c[2 * j + 1];
		        }
		        tmp_u += width / 2;
		        tmp_v += width / 2;
		    }

		    fwrite(tmp, 1, width * height, fp);
		    free(tmp);
		} break;
		case MPP_FMT_YUV420SP_VU :
		case MPP_FMT_YUV420SP : {
#if 0
			RK_U32 i;
			RK_U8 *base_y = base;
			RK_U8 *base_c = base + h_stride * v_stride;

			LOGD("Dump %d\n", fmt);
			for (i = 0; i < height; i++, base_y += h_stride) {
				fwrite(base_y, 1, width, fp);
			}
			for (i = 0; i < height / 2; i++, base_c += h_stride) {
				fwrite(base_c, 1, width, fp);
			}
#else
			RK_U32 i;
			RK_U8 *base_y = base;
			RK_U8 *base_u = base + h_stride * v_stride;
			RK_U8 *base_v = base_u + h_stride * v_stride / 4;

			for (i = 0; i < height; i++, base_y += h_stride)
				fwrite(base_y, 1, width, fp);
			for (i = 0; i < height / 2; i++, base_u += h_stride / 2)
				fwrite(base_u, 1, width / 2, fp);
			for (i = 0; i < height / 2; i++, base_v += h_stride / 2)
				fwrite(base_v, 1, width / 2, fp);
#endif
		} break;
		case MPP_FMT_YUV420P : {
			RK_U32 i;
			RK_U8 *base_y = base;
			RK_U8 *base_u = base + h_stride * v_stride;
			RK_U8 *base_v = base_u + h_stride * v_stride / 4;

			for (i = 0; i < height; i++, base_y += h_stride) {
				fwrite(base_y, 1, width, fp);
			}
			for (i = 0; i < height / 2; i++, base_u += h_stride / 2) {
				fwrite(base_u, 1, width / 2, fp);
			}
			for (i = 0; i < height / 2; i++, base_v += h_stride / 2) {
				fwrite(base_v, 1, width / 2, fp);
			}
			//LOGE("Dump YUV420P: W:H=%d:%d, WS:HS=%d:%d, Fmt=%s\n", width, height, h_stride, v_stride, mppFrameFormatToString(mpp_frame_get_fmt(frame)));
		} break;
		case MPP_FMT_YUV420SP_10BIT : {
			RK_U32 i, k;
			RK_U8 *base_y = base;
			RK_U8 *base_c = base + h_stride * v_stride;
			RK_U8 *tmp_line = (RK_U8 *)malloc(width);

			if (!tmp_line) {
				LOGE("tmp_line malloc fail");
				return;
			}

			for (i = 0; i < height; i++, base_y += h_stride) {
				for (k = 0; k < width / 8; k++) {
					RK_U16 *pix = (RK_U16 *)(tmp_line + k * 16);
					RK_U16 *base_u16 = (RK_U16 *)(base_y + k * 10);

					pix[0] =  base_u16[0] & 0x03FF;
					pix[1] = (base_u16[0] & 0xFC00) >> 10 | (base_u16[1] & 0x000F) << 6;
					pix[2] = (base_u16[1] & 0x3FF0) >> 4;
					pix[3] = (base_u16[1] & 0xC000) >> 14 | (base_u16[2] & 0x00FF) << 2;
					pix[4] = (base_u16[2] & 0xFF00) >> 8  | (base_u16[3] & 0x0003) << 8;
					pix[5] = (base_u16[3] & 0x0FFC) >> 2;
					pix[6] = (base_u16[3] & 0xF000) >> 12 | (base_u16[4] & 0x003F) << 4;
					pix[7] = (base_u16[4] & 0xFFC0) >> 6;
				}
				fwrite(tmp_line, width * sizeof(RK_U16) , 1, fp);
			}

			for (i = 0; i < height / 2; i++, base_c += h_stride) {
				for (k = 0; k < (width / 8); k++) {
					RK_U16 *pix = (RK_U16 *)(tmp_line + k * 16);
					RK_U16 *base_u16 = (RK_U16 *)(base_c + k * 10);

					pix[0] = base_u16[0] & 0x03FF;
					pix[1] = (base_u16[0] & 0xFC00) >> 10 | (base_u16[1] & 0x000F) << 6;
					pix[2] = (base_u16[1] & 0x3FF0) >> 4;
					pix[3] = (base_u16[1] & 0xC000) >> 14 | (base_u16[2] & 0x00FF) << 2;
					pix[4] = (base_u16[2] & 0xFF00) >> 8  | (base_u16[3] & 0x0003) << 8;
					pix[5] = (base_u16[3] & 0x0FFC) >> 2;
					pix[6] = (base_u16[3] & 0xF000) >> 12 | (base_u16[4] & 0x003F) << 4;
					pix[7] = (base_u16[4] & 0xFFC0) >> 6;
				}
				fwrite(tmp_line, width * sizeof(RK_U16) , 1, fp);
			}

			free(tmp_line);
		} break;
		case MPP_FMT_YUV444SP : {
			/* YUV444SP -> YUV444P for better display */
			RK_U32 i, j;
			RK_U8 *base_y = base;
			RK_U8 *base_c = base + h_stride * v_stride;
			RK_U8 *tmp = (RK_U8*)malloc(h_stride * height * 2);
			RK_U8 *tmp_u = tmp;
			RK_U8 *tmp_v = tmp + width * height;
			for (i = 0; i < height; i++, base_y += h_stride)
				fwrite(base_y, 1, width, fp);

			for (i = 0; i < height; i++, base_c += h_stride * 2) {
				for (j = 0; j < width; j++) {
					tmp_u[j] = base_c[2 * j + 0];
					tmp_v[j] = base_c[2 * j + 1];
				}
				tmp_u += width;
				tmp_v += width;
			}

			fwrite(tmp, 1, width * height * 2, fp);
			free(tmp);
		} break;
		case MPP_FMT_YUV400: {
			RK_U32 i;
			RK_U8 *base_y = base;
			RK_U8 *tmp = (RK_U8*)malloc(h_stride * height);

			for (i = 0; i < height; i++, base_y += h_stride)
				fwrite(base_y, 1, width, fp);

			free(tmp);
		} break;
		case MPP_FMT_ARGB8888:
		case MPP_FMT_ABGR8888:
		case MPP_FMT_BGRA8888:
		case MPP_FMT_RGBA8888: {
			RK_U32 i;
			RK_U8 *base_y = base;
			RK_U8 *tmp = (RK_U8*)malloc(width * height * 4);

			for (i = 0; i < height; i++, base_y += h_stride)
				fwrite(base_y, 1, width * 4, fp);

			free(tmp);
		} break;
		case MPP_FMT_RGB565:
		case MPP_FMT_BGR565:
		case MPP_FMT_RGB555:
		case MPP_FMT_BGR555:
		case MPP_FMT_RGB444:
		case MPP_FMT_BGR444: {
			RK_U32 i;
			RK_U8 *base_y = base;
			RK_U8 *tmp = (RK_U8*)malloc(width * height * 2);

			for (i = 0; i < height; i++, base_y += h_stride)
				fwrite(base_y, 1, width * 2, fp);

			free(tmp);
		} break;
		default : {
			LOGE("not supported format %d\n", fmt);
		} break;
	}
}
