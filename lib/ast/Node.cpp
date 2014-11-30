/*
 * Node.cpp
 *
 *  Created on: 2014/11/06
 *      Author: nakatani.sho
 */

#include "ast/Node.h"

namespace Smartdb {
namespace Ast {

Node::Node() {
  // TODO Auto-generated constructor stub

}

Node::~Node() {
  // TODO Auto-generated destructor stub
}

void* Smartdb::Ast::Node::operator new(size_t size, const Node* parent) {
  // [TODO] - link to parent Node (to batch delete from the root after Ast is used)
  return ::operator new(size);
}

void Smartdb::Ast::Node::operator delete(void* p) {
  // [TODO] - batch delete from the root
  ::operator delete(p);
}

}
} /* namespace Smartdb */
