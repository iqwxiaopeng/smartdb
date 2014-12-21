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

/**
 * Each Operator takes 1 of the following states at a given time:
 * WAITING: Child Operator does not even start outputting Records.
 *   Initial state of non-leaf Operator.
 * RUNNABLE: Child Operator already output at least a chunk of Records.
 *   But no Operator's instance is run on any worker.
 *   Initial state of leaf Operator.
 * RUNNING: Only difference from RUNNABLE is RUNNING Operator has at least one instance run on any worker.
 * FINISHED: Operator finished its execution.
 *
 * Possible state transition:
 *   WAITING --> RUNNABLE <--> RUNNING --> FINISHED
 *
 * @note state is shared among all instances of each Operator.
 */
enum SchedulingState {
  WAITING = 1,
  RUNNABLE,
  RUNNING,
  FINISHED,
};

enum OperationType {
  // Operator with single input
  /**
   * should get all the input records when starting calculation.
   * @example simple sort, simple aggregation, etc...
   */
  BLOCK = 1,
  /**
   * can process each record before getting all inputs.
   * @example filter, projection, etc...
   */
  STREAM,

  // Operator with double inputs
  /**
   * should get all the input records from both children operators when starting calculation.
   * @example UNION
   */
  BLOCK_BLOCK,
  /**
   * should get all the input records from one child operator.
   * After that, each record from another child operator can be processed without waiting for all.
   * @example INNER JOIN
   */
  BLOCK_STREAM,
  /**
   * can process each record from both children operators any time.
   * @example UNION ALL
   */
  STREAM_STREAM,
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
  inline static void to_runnable() {
    FOR_SCHEDULER_MAIN_THREAD
    ASSERT(state == WAITING || state == RUNNING);
    state = RUNNABLE;
  }
  /**
   * @note Called only from scheduler main thread.
   */
  inline static void to_running() {
    FOR_SCHEDULER_MAIN_THREAD
    ASSERT(state == RUNNABLE);
    state = RUNNING;
  }
  /**
   * @note Called only from scheduler main thread.
   */
  inline static void to_finished() {
    FOR_SCHEDULER_MAIN_THREAD
    ASSERT(state == RUNNING);
    state = FINISHED;
  }

  /**
   * @note Called only from scheduler main thread.
   */
  inline static bool is_finished() {
    FOR_SCHEDULER_MAIN_THREAD
    return state == FINISHED;
  }

  RecordsQueue out_q;

protected:
  static SchedulingState state;
};

}

#endif /* INCLUDE_OP_OPERATOR_H_ */
