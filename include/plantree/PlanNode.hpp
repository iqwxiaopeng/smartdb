/*
 * PlanNode.h
 *
 *  Created on: 2014/12/22
 *      Author: nakatani.sho
 */

#ifndef TEST_UNIT_LIB_PLANTREE_PLANNODE_H_
#define TEST_UNIT_LIB_PLANTREE_PLANNODE_H_

#include "plantree/PlanNodeId.hpp"
#include "op/OperatorParam.hpp"
#include "hack/Assert.hpp"
#include "hack/Class.hpp"
#include "hack/ForSchedulerMainThread.hpp"

namespace Smartdb {

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

class PlanNode {
public:
  PlanNode(PlanNodeId plan_node_id, const OperatorParam * const op_param, SchedulingState state = WAITING);
  ~PlanNode();

  /**
   * @note Called only from scheduler main thread.
   */
  inline void to_runnable() {
    FOR_SCHEDULER_MAIN_THREAD
    ASSERT(state == WAITING || state == RUNNING);
    state = RUNNABLE;
  }
  /**
   * @note Called only from scheduler main thread.
   */
  inline void to_running() {
    FOR_SCHEDULER_MAIN_THREAD
    ASSERT(state == RUNNABLE);
    state = RUNNING;
  }
  /**
   * @note Called only from scheduler main thread.
   */
  inline void to_finished() {
    FOR_SCHEDULER_MAIN_THREAD
    ASSERT(state == RUNNING);
    state = FINISHED;
  }

  /**
   * @note Called only from scheduler main thread.
   */
  inline bool is_finished() const {
    FOR_SCHEDULER_MAIN_THREAD
    return state == FINISHED;
  }

private:
  PlanNodeId plan_node_id;
  const OperatorParam * const op_param;
  SchedulingState state;

  PREVENT_CLASS_DEFAULT_METHODS(PlanNode);
};

} /* namespace Smartdb */

#endif /* TEST_UNIT_LIB_PLANTREE_PLANNODE_H_ */
