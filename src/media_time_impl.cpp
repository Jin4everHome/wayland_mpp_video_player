#include "media_time_impl.h"
#include "log.h"

#ifdef TAG
#undef TAG
#define TAG "MediaPlayer"
#endif


MediaTimeImpl::MediaTimeImpl(int64_t start_offset_usec)
{
	this->start_offset_time_ = start_offset_usec;
}

void MediaTimeImpl::Play()
{
	if(isPlaying_)
		return;

	std::lock_guard<std::mutex> guard(lock_);
	seek_time_ = GetCurrentMediaTime(&seek_time_set_at_);
	isPlaying_ = true;
}

void MediaTimeImpl::Start(int64_t start_offset_usec)
{
	std::lock_guard<std::mutex> guard(lock_);
	if (start_offset_usec) {
		start_offset_time_ = start_offset_usec;
	}
	seek_time_set_at_ =  getSystemTimeNow();
	seek_time_ = GetCurrentMediaTime(&seek_time_set_at_);
	isPlaying_ = true;
}

void MediaTimeImpl::Pause()
{
	if(!isPlaying_)
		return;

	std::lock_guard<std::mutex> guard(lock_);
	seek_time_ = GetCurrentMediaTime(&seek_time_set_at_);
	isPlaying_ = false;
}

void MediaTimeImpl::SetPlaybackRate(double playback_rate, bool isAudio)
{
	if (playback_rate_ == playback_rate)
		return;

	std::lock_guard<std::mutex> guard(lock_);
	seek_time_ = GetCurrentMediaTime(&seek_time_set_at_);

	isAudio_ = isAudio;
	playback_rate_ = playback_rate;
}

void MediaTimeImpl::Seek(mediaTime seek_to_time, int trickplay)
{
	std::lock_guard<std::mutex> guard(lock_);
	seek_time_ = seek_to_time;
	seek_time_set_at_ =  getSystemTimeNow();
}

mediaTime MediaTimeImpl::GetMediaTime( )
{
	std::lock_guard<std::mutex> guard(lock_);
	mediaTime current = GetCurrentMediaTime() + start_offset_time_;
	return current;
}

mediaTime MediaTimeImpl::GetCurrentMediaTime(int64_t *currentTime)
{
	systemTime now = getSystemTimeNow();
	if (!isPlaying_ || playback_rate_ == 0.0)
	{
		/*
		 * If pause -> play,
		 * just return last stored seek_time_
		 * and update seek_time_set_at_
		 */
		if (currentTime) {
			*currentTime = now;
		}
		return seek_time_;
	}

	/*
	 * If play to pause,
	 * Update time seek_time_ = seek_time_ + elapsed_ (from last seek time)
	 */
	systemTime elapsed = (now - seek_time_set_at_) * playback_rate_;
	if (currentTime)
		*currentTime = now;

	return seek_time_ + static_cast<mediaTime>(elapsed);
}

void MediaTimeImpl::SetTime(mediaTime time, int trickplay)
{
	std::lock_guard<std::mutex> guard(lock_);
	seek_time_ = time;
	seek_time_set_at_ =  getSystemTimeNow();
}
