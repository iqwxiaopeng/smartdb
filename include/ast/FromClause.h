/*
 * FromClause.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_FROMCLAUSE_H_
#define INCLUDE_AST_FROMCLAUSE_H_

#include <vector>
#include <string>
#include "Node.h"

namespace Smartdb {
namespace Ast {

class FromClause : public Node {
public:
  FromClause();
  virtual ~FromClause();

  std::vector<std::string> tables;
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_FROMCLAUSE_H_ */
