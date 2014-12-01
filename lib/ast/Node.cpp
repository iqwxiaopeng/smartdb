/*
 * Node.cpp
 *
 *  Created on: 2014/11/06
 *      Author: nakatani.sho
 */

#include "ast/Node.h"
#include "ast/Root.h"

namespace Smartdb {
namespace Ast {

Node::Node() {
  // TODO Auto-generated constructor stub

}

Node::~Node() {
  // TODO Auto-generated destructor stub
}

}
} /* namespace Smartdb */


//
// static functions

// @param root: NULL if allocating node is the root
void* Smartdb::Ast::Node::operator new(size_t size, Smartdb::Ast::Root* root) {
  Smartdb::Ast::Node * node = (Smartdb::Ast::Node *)::operator new(size);
  if (root) root->append_to_free_list(node);
  return node;

}

void Smartdb::Ast::Node::operator delete(void* p) {
  ::operator delete(p);
}
