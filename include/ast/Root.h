/*
 * Root.h
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_ROOT_H_
#define INCLUDE_AST_ROOT_H_

#include "ast/Node.h"

namespace Smartdb {
namespace Ast {

class Root : public Node {
public:
  static Root * ast_root;

  Root();
  virtual ~Root();


};

} /* namespace Ast */
} /* namespace Smartdb */

#endif /* INCLUDE_AST_ROOT_H_ */
