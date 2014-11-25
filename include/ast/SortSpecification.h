/*
 * OrderSpecification.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_SORTSPECIFICATION_H_
#define INCLUDE_AST_SORTSPECIFICATION_H_

#include "Node.h"
#include "Column.h"

namespace Smartdb {
namespace Ast {

class SortSpecification : public Node {
public:
 SortSpecification() : asc(true) {}
  virtual ~SortSpecification() = 0;

  const Column * const column;
  bool asc;
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_SORTSPECIFICATION_H_ */
