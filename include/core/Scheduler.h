/*
 * Scheduler.h
 *
 *  Created on: 2014/12/20
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_CORE_SCHEDULER_H_
#define INCLUDE_CORE_SCHEDULER_H_

#include <pthread.h>
#include "plantree/BinaryTree.h"
#include "hack/Class.h"

namespace Smartdb {

class Executor;
class PlanNode;

class Scheduler {
public:
  /**
   * Construct Scheduler.
   * @param executor
   * @param plantree
   * @note Although plantree is not const, Scheduler never changes state of plantree.
   */
  Scheduler(const Executor & executor, BinaryTree<PlanNode> & plantree);
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
  pthread_t scheduler_main_thread_tid;
  BinaryTree<PlanNode> & plantree;

  static void * main_loop(Scheduler *_this);

  PREVENT_CLASS_DEFAULT_METHODS(Scheduler);
};

} /* namespace Smartdb */

#endif /* INCLUDE_CORE_SCHEDULER_H_ */
