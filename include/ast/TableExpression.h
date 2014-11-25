/*
 * TableExpression.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_TABLEEXPRESSION_H_
#define INCLUDE_AST_TABLEEXPRESSION_H_

#include "Node.h"
#include "FromClause.h"
#include "OrderByClause.h"

namespace Smartdb {
namespace Ast {

class TableExpression : public Node {
public:
  TableExpression();
  virtual ~TableExpression();

  const FromClause * const from_clause;
  const OrderByClause * const order_by_clause;
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_TABLEEXPRESSION_H_ */
