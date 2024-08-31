#ifndef __NATIVE_SYSTEM_TIME_H__
#define __NATIVE_SYSTEM_TIME_H__

#include <stdint.h>

typedef int64_t mediaTime;
typedef int64_t systemTime;
 
systemTime getSystemTimeNow();
systemTime getSystemTimeNano();
 
#endif // __NATIVE_SYSTEM_TIME_H__
