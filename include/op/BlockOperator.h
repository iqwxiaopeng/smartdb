/*
 * BlockOperator.h
 *
 *  Created on: 2014/12/13
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_OP_BLOCKOPERATOR_H_
#define INCLUDE_OP_BLOCKOPERATOR_H_

#include "Operator.h"

namespace Smartdb {

class BlockOperator : public Operator {
public:
  BlockOperator();
  virtual ~BlockOperator();

  static const OperationType op_type = BLOCK;
};

} /* namespace Smartdb */

#endif /* INCLUDE_OP_BLOCKOPERATOR_H_ */
