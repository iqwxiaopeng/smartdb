/*
 * Scheduler.cpp
 *
 *  Created on: 2014/12/20
 *      Author: nakatani.sho
 */

#include "core/Scheduler.h"
#include "core/Executor.h"
#include "op/Operator.h"

namespace Smartdb {

Scheduler::Scheduler(const Executor & executor, Operator & root_op)
: root_op(root_op)
{

}

Scheduler::~Scheduler() {
}

void Scheduler::execute() {
  do {

  } while (!root_op.is_finished());
}

void Scheduler::join() {
}

} /* namespace Smartdb */
