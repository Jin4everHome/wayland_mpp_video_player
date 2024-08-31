// Copyright 2017 The Cobalt Authors. All Rights Reserved.
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

#include <stdint.h>
#include <pthread.h>
#include <sched.h>
#include <sys/resource.h>
#include <unistd.h>
#include <string.h>
#include <sys/prctl.h>
#include <assert.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <time.h>

#include "thread_wrapper.h"


#define PTHREAD_INTERNAL_THREAD(thread) reinterpret_cast<pthread_t>(thread)
#define PTHREAD_INTERNAL_THREAD_PTR(thread) reinterpret_cast<pthread_t *>(&(thread))

namespace mediaplayer {
namespace shared {
namespace pthread {

void SetNiceValue(int nice) {
  int result = setpriority(PRIO_PROCESS, 0, nice);
  if (result != 0) {
    assert(0);
  }
}

void ThreadSetPriority(ThreadPriority priority) {
  if (0/*!IsThreadPrioritySupport*/) {
    return;
  }

  switch (priority) {
    case kThreadPriorityLowest:
      SetNiceValue(19);
      break;
    case kThreadPriorityLow:
      SetNiceValue(10);
      break;
    case kThreadNoPriority:
    case kThreadPriorityNormal:
      SetNiceValue(0);
      break;
    case kThreadPriorityHigh:
      SetNiceValue(-8);
      break;
    case kThreadPriorityHighest:
      SetNiceValue(-16);
      break;
    case kThreadPriorityRealTime:
      SetNiceValue(-19);
      break;
    default:
      // TODO: error
      break;
  }
}

void PreThreadRun() {}
void PostThreadRun() {
}

}  // namespace pthread
}  // namespace shared
}  // namespace mediaplayer

namespace {

// Returns whether the given thread affinity is valid.
inline bool ThreadIsValidAffinity(int32_t affinity) {
  return affinity != (int32_t)(0x80000000);
}

struct ThreadParams {
  int32_t affinity; //SbThreadAffinity affinity;
  ThreadEntryPoint entry_point;
  char name[128];
  void* context;
  ThreadPriority priority;
};

void* ThreadFunc(void* context) {
  ThreadParams* thread_params = static_cast<ThreadParams*>(context);
  ThreadEntryPoint entry_point = thread_params->entry_point;
  void* real_context = thread_params->context;
  int32_t affinity = thread_params->affinity;
  if (thread_params->name[0] != '\0') {
    ThreadSetName(thread_params->name);
  }

  mediaplayer::shared::pthread::ThreadSetPriority(thread_params->priority);

  delete thread_params;

  if (ThreadIsValidAffinity(affinity)) {
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(affinity, &cpu_set);
    sched_setaffinity(0, sizeof(cpu_set), &cpu_set);
  }

  mediaplayer::shared::pthread::PreThreadRun();

  void* return_value = entry_point(real_context);

  mediaplayer::shared::pthread::PostThreadRun();

  return return_value;
}

}  // namespace

inline bool IsSuccess(int result_code) {
  return result_code == 0;
}


int32_t ThreadGetId() {
  // This is not portable outside of Linux.
  return static_cast<int32_t>(syscall(SYS_gettid));
} 

void ThreadSetName(const char* name) {
  // We don't want to rename the main thread.
  if (ThreadGetId() == getpid()) {
    return;
  }

  char buffer[2048];

  if (strlen(name) >= sizeof(buffer)) {
    strncpy(buffer, name, sizeof(buffer));
    name = buffer;
  }

  if (pthread_setname_np(pthread_self(), name) != 0) {
    //SB_DLOG(ERROR) << "Failed to set thread name to " << name;
  }
}

void ThreadGetName(char* buffer, int buffer_size) {
  prctl(PR_GET_NAME, buffer, 0L, 0L, 0L);
}

void ThreadSleep(uint64_t duration) {
  if (duration <= 0) {
    return;
  }
    
  // SbTime is microseconds, so this is easy.
  usleep(duration);
}   

kThread ThreadCreate(int64_t stack_size,
                        ThreadPriority priority,
                        int32_t affinity,
                        bool joinable,
                        const char* name,
                        ThreadEntryPoint entry_point,
                        void* context) {
  if (stack_size < 0 || !entry_point) {
    return kThreadInvalid;
  }

#if 1 //defined(ADDRESS_SANITIZER)
  // Set a big thread stack size when in ADDRESS_SANITIZER mode.
  // This eliminates buffer overflows for deeply nested callstacks.
  if (stack_size == 0) {
    stack_size = 4096 * 1024;  // 4MB
  }
#endif

  pthread_attr_t attributes;
  int result = pthread_attr_init(&attributes);
  if (!IsSuccess(result)) {
    return kThreadInvalid;
  }

  pthread_attr_setdetachstate(
      &attributes,
      (joinable ? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED));
  if (stack_size > 0) {
    pthread_attr_setstacksize(&attributes, stack_size);
  }

  ThreadParams* params = new ThreadParams();
  params->affinity = affinity;
  params->entry_point = entry_point;
  params->context = context;

  if (name) {
    strncpy(params->name, name, sizeof(params->name));
  } else {
    params->name[0] = '\0';
  }

  params->priority = priority;

  kThread thread = kThreadInvalid;
                    
  result = pthread_create(PTHREAD_INTERNAL_THREAD_PTR(thread), &attributes,
                          ThreadFunc, params);

  pthread_attr_destroy(&attributes);
  if (IsSuccess(result)) {
    return thread;
  }

  return kThreadInvalid;
}


bool ThreadJoin(kThread thread, void** out_return) {
  if (!ThreadIsValid(thread)) {
    return false;
  }

  void* joined_return = nullptr;
  int result = pthread_join(PTHREAD_INTERNAL_THREAD(thread), &joined_return);
  if (!IsSuccess(result)) {
    return false;
  }

  if (out_return) {
    *out_return = joined_return;
  }

  return true;
}


bool ThreadTimedJoin(kThread thread, void** out_return, int waittime_secs)
{
	struct timespec ts;

	if (!ThreadIsValid(thread)) {
	  return false;
	}

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
    {
        /* Handle error */
        return false;
    }

	void* joined_return = nullptr;

	ts.tv_sec += (time_t) waittime_secs;
	
	//int result = pthread_timedjoin_np(PTHREAD_INTERNAL_THREAD(thread), NULL, (const struct timespec *)&ts);
	int result = pthread_join(PTHREAD_INTERNAL_THREAD(thread), nullptr);
	if (!IsSuccess(result)) {
	  return false;
	}
	
	if (out_return) {
	  *out_return = joined_return;
	}
	
	return true;
}

ThreadLocalKey ThreadCreateLocalKey(ThreadLocalDestructor destructor) {
  ThreadLocalKey key = new ThreadLocalKeyPrivate();
  if (!IsSuccess(pthread_key_create(&key->key, destructor))) {
    delete key;
    return kThreadLocalKeyInvalid;
  }
  return key;
}

void* ThreadGetLocalValue(ThreadLocalKey key) {
  if (!ThreadIsValidLocalKey(key)) {
    return nullptr;
  }

  return pthread_getspecific(key->key);
}

bool ThreadSetLocalValue(ThreadLocalKey key, void* value) {
  if (!ThreadIsValidLocalKey(key)) {
    return false;
  }
  
  if (IsSuccess(pthread_setspecific(key->key, value))) {
    return true;
  } 
  
  return false;
}


