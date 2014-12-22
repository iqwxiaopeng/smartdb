/*
 * Scheduler.h
 *
 *  Created on: 2014/12/20
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_CORE_SCHEDULER_H_
#define INCLUDE_CORE_SCHEDULER_H_

#include <pthread.h>
#include "hack/Class.h"

namespace Smartdb {

class Executor;
class PlanNode;

class Scheduler {
public:
  Scheduler(const Executor & executor, const PlanNode & root_plan);
  virtual ~Scheduler();

  /**
   * Starts scheduler main thread.
   */
  void execute();
  /**
   * Wait for scheduler main thread to finish.
   */
  void join();

private:
  static void * main_loop(Scheduler *_this);

  pthread_t scheduler_main_thread_tid;
  const PlanNode & root_plan;

  PREVENT_CLASS_DEFAULT_METHODS(Scheduler);
};

} /* namespace Smartdb */

#endif /* INCLUDE_CORE_SCHEDULER_H_ */
