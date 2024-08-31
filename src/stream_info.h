#ifndef __STREAM_INFO_H__
#define __STREAM_INFO_H__

#define VID_HEADER_SIZE (8192)

typedef struct videoStreamInfo
{
	int index;      // stream_index
	int codec_id;

	int num_order;  // the number of order.

	int width;
	int height;
	int bitrate;
	PacketQueue *queue = NULL;

	AVFormatContext *fmx_ctx = NULL;
	AVCodecContext *vid_dec_ctx = NULL;
	AVStream* vid_stream = NULL;
	AVCodecParserContext* vid_parser = NULL;

	int vid_param_set = 0;
	int first = 1;
	int64_t first_timestamp = -1;
	int64_t last_timestamp = -1;
	int64_t last_keyframe_timestamp = -1;
	int64_t last_stopped_timestamp = -1;
	bool last_keyframe_timestamp_pending_ = false;

	int discard;
	int num_of_first;

	int64_t last_video_pts = -1;
	int     vid_header_size = 0;
	uint8_t vid_header[VID_HEADER_SIZE];
	bool isSupport;
}videoStreamInfo;

#endif //__STREAM_INFO_H__
