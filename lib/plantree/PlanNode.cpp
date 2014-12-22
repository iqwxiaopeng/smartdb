/*
 * PlanNode.cpp
 *
 *  Created on: 2014/12/22
 *      Author: nakatani.sho
 */

#include "plantree/PlanNode.h"

namespace Smartdb {

PlanNode::PlanNode(PlanNodeId op_type, SchedulingState state)
: plan_node_id(op_type), state(state)
{
}

PlanNode::~PlanNode() {
  // TODO Auto-generated destructor stub
}

} /* namespace Smartdb */
