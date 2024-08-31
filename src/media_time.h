#ifndef __NATIVE_MEDIA_TIME_H__
#define __NATIVE_MEDIA_TIME_H__

#include "system_time.h"

#define MEDIATIME_MICROSECONDS 1
#define MEDIATIME_MILLISECONDS 1000
#define MEDIATIME_SECONDS 1000000


class MediaTime {
public:
	virtual void Play() = 0;
	virtual void Pause() = 0;
 	virtual void SetPlaybackRate(double playback_rate, bool isAudio) = 0;
	virtual void Seek(mediaTime seekTime, int trickplay) = 0;
	virtual mediaTime GetMediaTime() = 0;
	virtual void SetTime(mediaTime time, int trickplay) = 0;

protected:
	virtual ~MediaTime() {}
};
#endif 
