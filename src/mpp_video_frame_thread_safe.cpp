#include "log.h"
#include "mpp_video_frame_thread_safe.h"


MppVideoFrameThreadSafe::MppVideoFrameThreadSafe()
	: count_(0)
{
	mpp_video_frames_.clear();
}

MppVideoFrameThreadSafe::~MppVideoFrameThreadSafe()
{
	std::lock_guard<std::mutex> mutex{ lock_};

	while(!mpp_video_frames_.empty()) {
		MppFrame frame = mpp_video_frames_.front();
		if (frame) {
			//frame->skipRelease();
			//count_--;
			//mpp_video_frames_.pop_front();
			mpp_frame_deinit(&frame);
			mpp_video_frames_.pop_front();
			count_--;
		}
		else {
			LOGE("(CRITICAL) queue front() should not be null\n");
			break;
		}
	}

	/*Debug*/
	if (count_ != 0) {
		LOGW("(CRITICAL) VideoFrame contrainer flushed, but remainings %d != 0\n", count_);
	}

	count_ = 0;
	mpp_video_frames_.clear();
}

size_t MppVideoFrameThreadSafe::size()
{
	size_t size = 0;
	std::lock_guard<std::mutex> mutex{ lock_};

	size = mpp_video_frames_.size();

	if (size < 0) {
		LOGE("(CRITICAL) invalid queue size %d\n", size);
		return 0;
	}

	if (size != count_) {
		LOGD("(CRITICAL) The number of item in video frame container are mismatch(%d : %d)\n", size, count_);
	}

	return size;
}

bool MppVideoFrameThreadSafe::empty()
{
	bool isEmpty = false;
	std::lock_guard<std::mutex> mutex{ lock_};

	isEmpty = mpp_video_frames_.empty();

	return isEmpty;
}

MppFrame MppVideoFrameThreadSafe::front()
{
	MppFrame frame = nullptr;
	std::lock_guard<std::mutex> mutex{ lock_};

	frame = mpp_video_frames_.front();

	return frame;
}

MppFrame MppVideoFrameThreadSafe::second()
{
	MppFrame frame = nullptr;
	std::lock_guard<std::mutex> mutex{ lock_};

	if (mpp_video_frames_.size() > 1) {
		auto second_iter = mpp_video_frames_.begin();
		frame = (*second_iter);
	}

	return frame;
}

MppFrame MppVideoFrameThreadSafe::back()
{
	MppFrame frame = nullptr;
	std::lock_guard<std::mutex> mutex{ lock_};

	if (!mpp_video_frames_.empty()) {
		frame = mpp_video_frames_.back();
	}

	return frame;
}

std::deque<MppFrame>::const_iterator  MppVideoFrameThreadSafe::begin()
{
	std::lock_guard<std::mutex> mutex{ lock_};
	return mpp_video_frames_.begin();
}

std::deque<MppFrame>::const_iterator  MppVideoFrameThreadSafe::end()
{
	std::lock_guard<std::mutex> mutex{ lock_};
	return mpp_video_frames_.end();
}

void MppVideoFrameThreadSafe::pop_front()
{
	std::lock_guard<std::mutex> mutex{ lock_};
	if (!mpp_video_frames_.empty()) {
		MppFrame frame = mpp_video_frames_.front();
		if (frame) {
			mpp_frame_deinit(&frame);
			mpp_video_frames_.pop_front();
			count_--;
			//mpp_frame_deinit(&frame);
		}
		else {
			LOGE("(CRITICAL) pop_front() No frame found\n");
		}
	}
	else {
		LOGE("(CRITICAL) No video frame found\n");
	}
}

void MppVideoFrameThreadSafe::push_back(MppFrame video_frame)
{
	if (!video_frame) {
		LOGW("Trying to push null instance to the queue, ignore...\n");
		return;
	}

	std::lock_guard<std::mutex> mutex{ lock_};
	mpp_video_frames_.push_back(video_frame);
	count_++;
}

void MppVideoFrameThreadSafe::flush()
{
	std::lock_guard<std::mutex> mutex{ lock_};

	while(!mpp_video_frames_.empty()) {
		MppFrame  frame = mpp_video_frames_.front();
		if (frame) {
			mpp_video_frames_.pop_front();
			count_--;
			//mpp_frame_deinit(&frame);
		}
		else {
			LOGE("(CRITICAL) queue front() should not be null\n");
			break;
		}
	}

	/*Debug*/
	if (count_ != 0) {
		LOGW("(CRITICAL) VideoFrame contrainer flushed, but remainings %d != 0\n", count_);
	}
	mpp_video_frames_.clear();
}

