#ifndef __MEDIA_PLYAER_H__
#define __MEDIA_PLYAER_H__

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include <functional>
#include <string>

#ifdef __cplusplus
extern "C"
{
#endif
#include "libavutil/imgutils.h"
#include "libavutil/samplefmt.h"
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
#ifdef __cplusplus
}
#endif

#include <rockchip/rk_mpi.h>

#include "thread_wrapper.h"
#include "packet_queue.h"
#include "stream_info.h"
#include "media_time_impl.h"
#include "mppDisplayInfo.h"

/* IF set, enable Wayland Video Renderer */
#define USE_WAYLAND_RENDERER 1

#if USE_WAYLAND_RENDERER
#include "egl_display.h"
#endif

#include "modeset.h"
#include "mpp_video_frame_thread_safe.h"

typedef std::function<void(MppFrame *dstFrm)> OutputCB;

class MediaPlayer {
public:
	MediaPlayer();
	MediaPlayer(const char *dumpfile_path);
	~MediaPlayer();

	int init(const char *uri, int flags);
	int deinit();

	int startPlay(int64_t start_time);
	int pausePlay();
	int resumePlay();
	int seek(int64_t seek_to_secs, int flag);
	int64_t getDuration();
	int64_t getPlayerTime();
	int64_t getMediaTime();
	bool isEOS();

	bool isInitDone() const { return init_done_; }
	bool isWorkerActive( ) const { return worker_active_; }

private:
	/* ffmpeg context */
	AVFormatContext*      av_fmt_ctx_ = nullptr;
	AVCodecContext*       av_vid_dec_ctx_= nullptr;
	AVStream*             av_stream_ = nullptr;
	AVCodecParserContext* av_vid_parser_ = nullptr;
	enum AVPixelFormat    av_pix_fmt_;

	enum InputType {
	  INPUT_TYPE_CODEC_CONFIG,
	  INPUT_TYPE_STREAM,
	  INPUT_TYPE_EOS,
	};

	struct PendingPacketInput {
		bool valid = false;
		enum InputType type = INPUT_TYPE_STREAM;
		AVPacket *avPacket = NULL;
		int id = 0;
		void *handle = nullptr;
	};

	AVPacket *avPacket_ = NULL;
	PendingPacketInput PendingPacketInput_;

	/* input parameter */
	std::string url_;
	int flags_;
	int start_time_ = 0;            // desired media start time(milliseconds) based on 0
	int video_stream_idx_ = -1;     // current video stream id
	int     vid_header_size_ = 0;
	uint8_t vid_header_[VID_HEADER_SIZE];

	videoStreamInfo * videoStreamInfo_=nullptr;

	int64_t duration_msec_ = 0LL;
	int64_t start_offset_  = 0LL;  // stream start_time

	bool init_done_ = false;
	bool seeking_ = false;
	bool flushing_ = false;
	bool paused_ = false;
	bool exiting_ = false;
	bool exitted_ = false;
	bool vid_eos_set_ = false;
	bool reseting_ = false;

	/* seek */
	int   seek_req_ = false;
	int64_t seek_pos_ = 0LL; // milliseconds
	int   seek_flags_ = 0;
	int   seek_by_external_ = 0;
	bool  seek_done_wait_ = false;
	int64_t last_seek_target_ = 0LL;

	int64_t packet_read_time_ = 0LL; // read packet start time at every packet 
	int64_t packet_seek_time_ = 0LL;

	int64_t firstVideoTimestamp_ = -1;
	int64_t lastVideoTimestamp_ = 0;
	int64_t firstPacketPts_ = -1;
	int64_t lastPacketPts_ = 0;
	int64_t firstPacketTimeStamp_ = -1;
	int64_t lastPacketTimeStamp_ = 0;

	int decoding_frames_ = 0;
	int decoded_frames_ = 0;
	int rendered_frames_ = 0;
	int dropped_frames_ = 0;

	bool first_packet_received_ = false;
	bool is_codec_cofig_required_ = false;

	MediaTime *mediaTimeHandle_ = NULL;
	std::unique_ptr<MediaTimeImpl> mediaTimeProvider_;

	pthread_mutex_t   lock_seek_;

	/* MPP */
	MppCodingType mMppCodingType;

	RK_S64 mTimeS;
	RK_S64 mTimeE;
	RK_S64 mTimeDiff;
	double mFrmRate;

	int mSrcW;
	int mSrcH;
	int mDstW;
	int mDstH;

	int mStrideW;
	int mStrideH;

	mppDisplayInfo mFrameDispInfo; // instead of mSrc ... mStrideW
	mppDisplayInfo mOutDispInfo;

	char *mPktBuf;      // Will deprecated...

	int mPktCnt = 0;   // Total Decoding and decoded Packet count
	int mFrameCnt = 0; // Total Decodeded frame Count
	int mRenderCnt = 0;// Total Rendered frame count
	MppCtx mCtx;
	MppApi *mApi;
	MppPacket mPkt;
	MppBuffer mBuffer;
	MppBufferGroup mFrmGrp;
	MppBufferGroup mExtFrmGrp;
	MppCodingType mCodecId= MPP_VIDEO_CodingAVC;

	/* Do not enable */
	MppFrameFormat mRGAOutputFmt = MPP_FMT_YUV420SP; // MPP_FMT_YUV420P, MPP_FMT_YUV420SP, MPP_FMT_ARGB8888

#if USE_WAYLAND_RENDERER
	std::unique_ptr<EGLDisplayOut> mEGLDevice = nullptr;
#endif

	sp_dev *mDev;
	sp_plane **mPlanes;
	sp_crtc *mCrtc;
	sp_plane *mTestPlane;

	int finalize();
	int initialize();

	MppPacket getMppPacket(void* data, size_t size, int64_t pts);
	int sendMppPacket(MppPacket packet, int timeout_ms);
	int sendCodecData(void* data, size_t size);
	int sendEosData(int timeout_ms);

	int setExternalBuffer(int size, int count);

	bool mUseExteranlBuffer = true;

	enum MPP_PACKET_FLAG {
		MPP_PACKET_FLAG_NONE = 0,
		MPP_PACKET_FLAG_EOS = 1,
		MPP_PACKET_FLAG_EXTRADATA = 2,
	};

#define NUM_OF_RENDER_FRAMES 1

	MppFrame mLastFrame;
	MppFrame mRenderFrame[NUM_OF_RENDER_FRAMES];

	MppVideoFrameThreadSafe mpp_video_frames_;

	void Decode(AVPacket *packet);
	void Reset();
	int GetMaxDecodeRequests();

	int outputFormatChanged(MppFrame frame);

	bool worker_active_ = false;
	int fill_header_video(AVCodecContext *dec_ctx, int stream_idx);
	int openCodecContext(int* stream_idx, AVCodecContext **dec_ctx, AVFormatContext *fmt_ctx, bool best_effort);

	/* EOS */
	bool eos_written_ = false;
	bool eos_decoded_ = false;
	bool eos_consumed_ = false;
	bool isEOSWritten();
	bool isEOSPlayed();

	bool isWritable();

	bool first_frame_rendered_ = false;
	bool isFirstFrameRendered();

	PacketQueue *packetQueue_ = NULL;
	int queuePacket(AVPacket *packet);
	void getFitScreenCordination(const MppFrame frame, bool isRotate, uint32_t& x, uint32_t& y, uint32_t& width, uint32_t& height);
	int decodeVideoPacket();
	int renderFrame();
	int renderOneDrmFrame(MppFrame frame);

	kThread dataThread_ = kThreadInvalid;
	bool dataThreadRunning_ = false;
	static void* dataThreadEntryPoint(void* context);
	void dataThreadFunc();

	kThread decoderThread_ = kThreadInvalid;
	bool decoderThreadRunning_ = false;
	static void* decoderThreadEntryPoint(void* context);
	void decoderThreadFunc();

	kThread renderThread_ = kThreadInvalid;
	bool renderThreadRunning_ = false;
	static void* renderThreadEntryPoint(void* context);
	void renderThreadFunc();

	MppFrame getRenderFrame(int consumed);

	// Debug only
	std::string dumpfile_;
	FILE  *dumpfp_ = nullptr;
	int dumpCnt_ = 0;


	void dumpFrameToFile(MppFrame frame, FILE *fp);
};

#endif // __MEDIA_PLYAER_H__
