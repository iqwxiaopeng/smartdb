/*
 * OrderByClause.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_ORDERBYCLAUSE_H_
#define INCLUDE_AST_ORDERBYCLAUSE_H_

#include "Node.h"
#include "SortSpecification.h"

namespace Smartdb {
namespace Ast {

class OrderByClause : public Node {
public:
  OrderByClause();
  virtual ~OrderByClause();

  const std::vector<const SortSpecification *> * sort_specification_list;
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_ORDERBYCLAUSE_H_ */
