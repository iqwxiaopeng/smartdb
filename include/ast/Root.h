/*
 * Root.h
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_ROOT_H_
#define INCLUDE_AST_ROOT_H_

#include <list>
#include "ast/Node.h"
#include "hack/Class.h"

namespace Smartdb {
namespace Ast {

enum RootType {
  UNDEF = 0,
  SELECT_STATEMENT,
};

class Root : public Node {
public:
  static Root * ast_root;

  Root();
  virtual ~Root();

  void append_to_free_list(Node * node);

  RootType root_type;
  Node * root_node;

private:
  std::list<Node *> node_free_list;

  PREVENT_COPY_CONSTRUCTOR(Root);
  PREVENT_OBJECT_ASSIGNMENT(Root);
};

} /* namespace Ast */
} /* namespace Smartdb */

#endif /* INCLUDE_AST_ROOT_H_ */
