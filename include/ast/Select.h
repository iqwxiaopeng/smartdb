/*
 * Select.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_SELECT_H_
#define INCLUDE_AST_SELECT_H_

#include "Node.h"
#include "SelectList.h"
#include "TableExpression.h"

namespace Smartdb {
namespace Ast {

class Select : public Node {
public:
  Select();
  virtual ~Select();

  const SelectList * const select_list;
  const TableExpression * const table_expression;
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_SELECT_H_ */
