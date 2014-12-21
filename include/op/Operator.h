/*
 * Operator.h
 *
 *  Created on: 2014/10/28
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_OP_OPERATOR_H_
#define INCLUDE_OP_OPERATOR_H_

#include "datastruct/RecordsQueue.h"
#include "hack/Assert.h"
#include "hack/ForSchedulerMainThread.h"

namespace Smartdb {

class RecordsQueue;
class Scheduler;

enum SchedulingState {
  WAITING = 1,
  RUNNABLE,
  RUNNING,
  FINISHED,
};

enum OperationType {
  BLOCK = 1,  // should get all the input records when starting calculation.
              // e.g. simple sort, simple aggregation, etc...
  STREAM,     // can process each record before getting all inputs.
              // e.g. filter, projection, etc...
};

class Operator {
public:
  Operator();
  virtual ~Operator();

  /**
   * Scheduler calls this function to make this operator RUNNING.
   * In this function, scheduler's member function must be called following these rules:
   * (1) call scheduler->on_records_output(): when Records are output
   * (2) call scheduler->on_operator_finished(): when Operator finishes its execution
   */
  virtual SmartdbErr run(const Scheduler & scheduler) = 0;

  /**
   * @note Called only from scheduler main thread.
   */
  void to_waiting() {
    FOR_SCHEDULER_MAIN_THREAD
    ASSERT(state == RUNNING);
    state = WAITING;
  }
  /**
   * @note Called only from scheduler main thread.
   */
  void to_runnable() {
    FOR_SCHEDULER_MAIN_THREAD
    ASSERT(state == WAITING);
    state = RUNNABLE;
  }
  /**
   * @note Called only from scheduler main thread.
   */
  void to_running() {
    FOR_SCHEDULER_MAIN_THREAD
    ASSERT(state == RUNNABLE);
    state = RUNNING;
  }
  /**
   * @note Called only from scheduler main thread.
   */
  void to_finished() {
    FOR_SCHEDULER_MAIN_THREAD
    ASSERT(state == RUNNING);
    state = FINISHED;
  }

  /**
   * @note Called only from scheduler main thread.
   */
  bool is_finished() const {
    FOR_SCHEDULER_MAIN_THREAD
    return state == FINISHED;
  }

  RecordsQueue out_q;

protected:

  SchedulingState state;
  OperationType op_type;
};

}

#endif /* INCLUDE_OP_OPERATOR_H_ */
