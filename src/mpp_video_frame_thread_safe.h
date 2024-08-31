#ifndef __MPP_VIDEO_FRAME_THREAD_SAFE_H__
#define __MPP_VIDEO_FRAME_THREAD_SAFE_H__
#include <memory>
#include <list>
#include <deque>
#include <mutex>
#include <rockchip/rk_mpi.h>

class MppVideoFrameThreadSafe
{
public:
	MppVideoFrameThreadSafe( );

	~MppVideoFrameThreadSafe( );

	size_t size();

	bool empty();

	MppFrame front();
	MppFrame second();
	MppFrame back();

	std::deque<MppFrame>::const_iterator  begin();
	std::deque<MppFrame>::const_iterator  end();

	void pop_front();
	void push_back(MppFrame video_frame);
	void flush();

private:

	std::deque<MppFrame> mpp_video_frames_;

	std::mutex lock_;
	int count_ = 0;
};


#endif // __MPP_VIDEO_FRAME_THREAD_SAFE_H__
