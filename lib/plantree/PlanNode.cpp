/*
 * PlanNode.cpp
 *
 *  Created on: 2014/12/22
 *      Author: nakatani.sho
 */

#include "plantree/PlanNode.h"

namespace Smartdb {

PlanNode::PlanNode(PlanNodeId op_type, const OperatorParam * const op_param, SchedulingState state)
: plan_node_id(op_type), op_param(op_param), state(state)
{
}

PlanNode::~PlanNode() {
  // TODO Auto-generated destructor stub
}

} /* namespace Smartdb */
