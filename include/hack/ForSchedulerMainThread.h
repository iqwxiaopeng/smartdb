/*
 * ForSchedulerMainThread.h
 *
 *  Created on: 2014/12/20
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_HACK_FORSCHEDULERMAINTHREAD_H_
#define INCLUDE_HACK_FORSCHEDULERMAINTHREAD_H_

#include <pthread.h>
#include "hack/Assert.h"

#define _SCHEDULER_MAIN_THREAD_ID_INITIAL_VAL 0

static pthread_t _scheduler_main_thread_tid = _SCHEDULER_MAIN_THREAD_ID_INITIAL_VAL;

/**
 * Declare this macro in any code path to assert the path is executed by scheduler main thread.
 * @note Call `set_scheduler_main_thread_tid()` beforehand.
 */
#define FOR_SCHEDULER_MAIN_THREAD \
  { \
    ASSERT(_scheduler_main_thread_tid != _SCHEDULER_MAIN_THREAD_ID_INITIAL_VAL); \
    ASSERT(pthread_self() == _scheduler_main_thread_tid); \
  }

/**
 * @param tid pthread_self() @ scheduler main thread.
 */
inline void set_scheduler_main_thread_tid(pthread_t tid) {
  _scheduler_main_thread_tid = tid;
}


#endif /* INCLUDE_HACK_FORSCHEDULERMAINTHREAD_H_ */
