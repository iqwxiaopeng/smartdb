/*
 * Operator.h
 *
 *  Created on: 2014/10/28
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_OP_OPERATOR_H_
#define INCLUDE_OP_OPERATOR_H_

#include "datastruct/RecordsQueue.hpp"
#include "hack/Assert.hpp"

namespace Smartdb {

class RecordsQueue;
class Scheduler;

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

  RecordsQueue out_q;
};

}

#endif /* INCLUDE_OP_OPERATOR_H_ */
