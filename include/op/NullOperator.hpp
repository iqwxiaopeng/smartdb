/*
 * NullOperator.h
 *
 *  Created on: 2014/12/20
 *      Author: nakatani.sho
 */

#ifndef LIB_OP_NULLOPERATOR_H_
#define LIB_OP_NULLOPERATOR_H_

#include "op/Operator.hpp"
#include "api/SmartdbType.hpp"

namespace Smartdb {

class NullOperator : public Operator {
public:
  NullOperator();
  virtual ~NullOperator();

  SmartdbErr run(const Scheduler & scheduler) { return NO_ERR; }
};

} /* namespace Smartdb */

#endif /* LIB_OP_NULLOPERATOR_H_ */
