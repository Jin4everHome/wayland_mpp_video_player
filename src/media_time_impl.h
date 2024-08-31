#ifndef __NATIVE_MEDIA_TIME_IMPL_H__
#define __NATIVE_MEDIA_TIME_IMPL_H__

#include "system_time.h"
#include "media_time.h"

#include <memory>
#include <mutex>
//#include <optional>

class MediaTimeImpl : public MediaTime {

public:
	MediaTimeImpl(int64_t start_offset_usec = 0LL);
	//explicit MediaTimeImpl(std::unique_ptr<MonotonicSystemTime> system_time_provider);

	void Play() override;
	void Pause() override;
	void SetPlaybackRate(double playback_rate, bool isAudio) override;
	void Seek(mediaTime seek_time, int trickplay) override;
	mediaTime GetMediaTime() override;
	void SetTime(mediaTime time, int trickplay) override;

	void Start(int64_t start_offset_time = 0);
	int64_t GetSystemTime() {return getSystemTimeNow();}

private:
	mediaTime GetCurrentMediaTime(int64_t *current_time = NULL);

	double playback_rate_ = 1.0;
	bool   isPlaying_ = false;
	bool   isAudio_ = true;
	mediaTime seek_time_ = 0LL;
	int64_t start_offset_time_;

	int trickplay_ = 0;

	std::mutex lock_;

	systemTime seek_time_set_at_ = getSystemTimeNow();
};

#endif // __NATIVE_MEDIA_TIME_IMPL_H__



