/*
 * Select.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_SELECTSTATEMENT_H_
#define INCLUDE_AST_SELECTSTATEMENT_H_

#include "Node.h"

namespace Smartdb {
namespace Ast {

class SelectStatement : public Node {
public:
  SelectStatement();
  virtual ~SelectStatement();

  bool select_list_all;  // SELECT * FROM ...
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_SELECTSTATEMENT_H_ */
