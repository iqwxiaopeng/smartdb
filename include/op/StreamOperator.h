/*
 * StreamOperator.h
 *
 *  Created on: 2014/12/13
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_OP_STREAMOPERATOR_H_
#define INCLUDE_OP_STREAMOPERATOR_H_

#include "Operator.h"

namespace Smartdb {

class StreamOperator : public Operator {
public:
  StreamOperator();
  virtual ~StreamOperator();
};

} /* namespace Smartdb */

#endif /* INCLUDE_OP_STREAMOPERATOR_H_ */
