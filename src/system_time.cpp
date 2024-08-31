#include <time.h>
#include "system_time.h"

systemTime getSystemTimeNow()
{
	struct timespec time;

	int64_t secs;
	int64_t usecs;

	if (clock_gettime(CLOCK_MONOTONIC, &time) != 0) {
		// TODO: print error
		return 0;
	}

	secs = static_cast<int64_t>(time.tv_sec)*1000000LL;
	usecs = static_cast<int64_t>(time.tv_nsec)/1000LL;

	return secs + usecs;
}

systemTime getSystemTimeNano()
{
	timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) {
		return 0;
	}

	return now.tv_sec * 1000000000LL + now.tv_nsec;
}


