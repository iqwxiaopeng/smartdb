/*
 * Scheduler.cpp
 *
 *  Created on: 2014/12/20
 *      Author: nakatani.sho
 */

#include <pthread.h>
#include "core/Scheduler.h"
#include "core/Executor.h"
#include "plantree/PlanNode.h"
#include "hack/ForSchedulerMainThread.h"

namespace Smartdb {

Scheduler::Scheduler(const Executor & executor, BinaryTree<PlanNode> & plantree)
: scheduler_main_thread_tid(0), plantree(plantree)
{
}

Scheduler::~Scheduler() {
}

void Scheduler::execute() {
  pthread_create(&scheduler_main_thread_tid, NULL, (void *(*)(void *))Scheduler::main_loop, this);
}

void Scheduler::join() {
  pthread_join(scheduler_main_thread_tid, NULL);
}

void * Scheduler::main_loop(Scheduler * _this) {
  set_scheduler_main_thread_tid(_this->scheduler_main_thread_tid);  // Necessary to use FOR_SCHEDULER_MAIN_THREAD
  FOR_SCHEDULER_MAIN_THREAD

  // Instantiate leaf operators (w/ 1 input Records)

  while (!_this->plantree.get_root()->is_finished()) {
    // update plan-tree status and run_q


    // while (run_q is not empty && workers are not full)
    //   search vacant worker and run op with highest priority on it

    // cond wait (慎重に(というか排他的に) conditional variable が更新されていないかは見る)

    // waken up by an operator (via callback)


  }
  return NULL;
}

} /* namespace Smartdb */
