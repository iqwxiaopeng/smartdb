/*
 * Node.h
 *
 *  Created on: 2014/11/06
 *      Author: nakatani.sho
 */

#ifndef LIB_AST_NODE_H_
#define LIB_AST_NODE_H_

#include "api/SmartdbType.h"

namespace Smartdb {
namespace Ast {

class Node {
public:
  Node();
  virtual ~Node();

  static void * operator new(size_t size, const Node * parent);
  static void operator delete(void * p);
};

}
} /* namespace Smartdb */

#endif /* LIB_AST_NODE_H_ */
