/*
 * Descending.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_DESCENDING_H_
#define INCLUDE_AST_DESCENDING_H_

#include "OrderSpecification.h"

namespace Smartdb {
namespace Ast {

class Descending : public SortSpecification {
public:
  Descending();
  virtual ~Descending();
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_DESCENDING_H_ */
