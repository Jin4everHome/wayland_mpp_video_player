// Copyright 2015 The Cobalt Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Module Overview: Starboard Thread module
//
// Defines functionality related to thread creation and cleanup.


#ifndef __THREAD_WRAPPER_H__
#define __THREAD_WRAPPER_H__
#include <pthread.h>

#define EXPORT_FUNC __attribute__((visibility("default")))

#define IsThreadPrioritySupport   0
#define kThreadInvalid            nullptr

struct ThreadLocalKeyPrivate {
  // The underlying thread-local variable handle.
  pthread_key_t key;
};

typedef struct ThreadLocalKeyPrivate ThreadLocalKeyPrivate;

typedef ThreadLocalKeyPrivate* ThreadLocalKey;

// Well-defined constant value to mean "no thread local key."
#define kThreadLocalKeyInvalid (ThreadLocalKey) NULL


// Returns whether the given thread local variable key is valid.
static inline bool ThreadIsValidLocalKey(ThreadLocalKey key) {
  return key != kThreadLocalKeyInvalid;
}

//
// In particular, several of these priority values can map to the same priority
// on a given platform. The only guarantee is that each lower priority should be
// treated less-than-or-equal-to a higher priority.
typedef enum ThreadPriority {
  // The lowest thread priority available on the current platform.
  kThreadPriorityLowest,

  // A lower-than-normal thread priority, if available on the current platform.
  kThreadPriorityLow,

  // Really, what is normal? You should spend time pondering that question more
  // than you consider less-important things, but less than you think about
  // more-important things.
  kThreadPriorityNormal,
  
  // A higher-than-normal thread priority, if available on the current platform.
  kThreadPriorityHigh,

  // The highest thread priority available on the current platform that isn't
  // considered "real-time" or "time-critical," if those terms have any meaning
  // on the current platform.
  kThreadPriorityHighest,

  // If the platform provides any kind of real-time or time-critical scheduling,
  // this priority will request that treatment. Real-time scheduling generally
  // means that the thread will have more consistency in scheduling than
  // non-real-time scheduled threads, often by being more deterministic in how
  // threads run in relation to each other. But exactly how being real-time
  // affects the thread scheduling is platform-specific.
  //
  // For platforms where that is not offered, or otherwise not meaningful, this
  // will just be the highest priority available in the platform's scheme, which
  // may be the same as kSbThreadPriorityHighest.
  kThreadPriorityRealTime,
  
  // Well-defined constant value to mean "no priority."  This means to use the
  // default priority assignment method of that platform. This may mean to
  // inherit the priority of the spawning thread, or it may mean a specific
  // default priority, or it may mean something else, depending on the platform.
  kThreadNoPriority = (int32_t)0x80000000,
} ThreadPriority;


// An opaque handle to a thread type.
//typedef void* SbThread
// Transparent pthread handle.
typedef void* kThread;

// Function pointer type for ThreadCreate.  |context| is a pointer-sized bit
// of data passed in from the calling thread.
typedef void* (*ThreadEntryPoint)(void* context);

// Function pointer type for Thread-Local destructors.
typedef void (*ThreadLocalDestructor)(void* value);


// Returns whether the given thread handle is valid.
static inline bool ThreadIsValid(kThread thread) {
  return thread != kThreadInvalid;
}

EXPORT_FUNC int32_t ThreadGetId();

EXPORT_FUNC void ThreadSetName(const char* name);

EXPORT_FUNC void ThreadGetName(char* buffer, int buffer_size);

EXPORT_FUNC void ThreadSleep(uint64_t duration);

EXPORT_FUNC kThread ThreadCreate(int64_t stack_size,
                        ThreadPriority priority,
                        int32_t affinity,
                        bool joinable,
                        const char* name,
                        ThreadEntryPoint entry_point,
                        void* context);

EXPORT_FUNC bool ThreadJoin(kThread thread, void** out_return);

EXPORT_FUNC bool ThreadTimedJoin(kThread thread, void** out_return, int waittime_secs);

EXPORT_FUNC ThreadLocalKey ThreadCreateLocalKey(ThreadLocalDestructor destructor);

EXPORT_FUNC void* ThreadGetLocalValue(ThreadLocalKey key);

EXPORT_FUNC bool ThreadSetLocalValue(ThreadLocalKey key, void* value);

#endif //__THREAD_WRAPPER_H__

