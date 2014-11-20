/*
 * Operator.h
 *
 *  Created on: 2014/10/28
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_OP_OPERATOR_H_
#define INCLUDE_OP_OPERATOR_H_

#include "datastruct/RecordsQueue.h"

namespace Smartdb {

class Operator {
public:
  Operator();
  virtual ~Operator();

  RecordsQueue out_q;
};

}

#endif /* INCLUDE_OP_OPERATOR_H_ */
