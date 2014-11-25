/*
 * Ascending.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_ASCENDING_H_
#define INCLUDE_AST_ASCENDING_H_

#include "OrderSpecification.h"

namespace Smartdb {
namespace Ast {

class Ascending : public OrderSpecification {
public:
  Ascending();
  virtual ~Ascending();
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_ASCENDING_H_ */
