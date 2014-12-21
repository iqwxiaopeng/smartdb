/*
 * Operator.cpp
 *
 *  Created on: 2014/10/28
 *      Author: nakatani.sho
 */

#include "op/Operator.h"

namespace Smartdb {

SchedulingState Operator::state = WAITING;

Operator::Operator()
: out_q()
{
  // TODO Auto-generated constructor stub

}

Operator::~Operator() {
  // TODO Auto-generated destructor stub
}

}
