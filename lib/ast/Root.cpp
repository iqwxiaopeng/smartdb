/*
 * Root.cpp
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#include "ast/Root.h"

namespace Smartdb {
namespace Ast {

Root * Root::ast_root = 0;

Root::Root()
: root_type(UNDEF), root_node(0)
{
}

Root::~Root() {
  for (std::list<Node *>::iterator it = node_free_list.begin();
       it != node_free_list.end(); ++it)
  { delete *it; }
}

void Root::append_to_free_list(Node * node) {
  node_free_list.push_back(node);
}

}
}
