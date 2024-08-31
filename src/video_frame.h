#ifndef __NATIVE_VIDEO_FRAME_H__
#define __NATIVE_VIDEO_FRAME_H__
#include <stdint.h>

class VideoFrame {
public:
	explicit VideoFrame(int64_t timestamp) : timestamp_(timestamp) { }

	virtual ~VideoFrame() {}

	int64_t getTimeStamp( ) const {return timestamp_;}

private:
	int64_t timestamp_;
}; // class video frame

#endif //__NATIVE_VIDEO_FRAME_H__
