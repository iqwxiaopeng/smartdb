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

  // Children operators call this function just after pushing records to out_q.
  // this operator may change its state from WAITING to RUNNABLE in the function.
  virtual void got_input_records(const Operator * const child_op) = 0;

  // Scheduler calls this function to make this operator RUNNING.
  // This function sends notification to scheduler after RUNNING state ends.
  virtual SmartdbErr run(Scheduler * const scheduler) = 0;

  RecordsQueue out_q;

protected:
  // Children operators, not the scheduler, call these state-transition functions
  void to_waiting() {
    ASSERT(state == RUNNING);
    state = WAITING;
  }
  void to_runnable() {
    ASSERT(state == WAITING);
    state = RUNNABLE;
  }
  void to_running() {
    ASSERT(state == RUNNABLE);
    state = RUNNING;
  }
  void to_finished() {
    ASSERT(state == RUNNING);
    state = FINISHED;
  }

  SchedulingState state;
  OperationType op_type;
};

}

#endif /* INCLUDE_OP_OPERATOR_H_ */
