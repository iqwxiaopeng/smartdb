/*
 * Node.h
 *
 *  Created on: 2014/11/06
 *      Author: nakatani.sho
 */

#ifndef LIB_AST_NODE_H_
#define LIB_AST_NODE_H_

#include "api/SmartdbType.hpp"

namespace Smartdb {
namespace Ast {

class Root;

class Node {
public:
  Node();
  virtual ~Node();

  // append newly created Node to free-list
  static void * operator new(size_t size, Smartdb::Ast::Root * root);
  static void operator delete(void * p);
};

}
} /* namespace Smartdb */

#endif /* LIB_AST_NODE_H_ */
