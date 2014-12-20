/*
 * Scheduler.h
 *
 *  Created on: 2014/12/20
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_CORE_SCHEDULER_H_
#define INCLUDE_CORE_SCHEDULER_H_

#include "hack/Class.h"

namespace Smartdb {

class Executor;
class Operator;

class Scheduler {
public:
  Scheduler(const Executor & executor, Operator & root_op);
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
  Operator & root_op;

  PREVENT_CLASS_DEFAULT_METHODS(Scheduler);
};

} /* namespace Smartdb */

#endif /* INCLUDE_CORE_SCHEDULER_H_ */
