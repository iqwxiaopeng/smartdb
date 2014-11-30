/*
 * Select.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_SELECT_H_
#define INCLUDE_AST_SELECT_H_

#include "Node.h"

namespace Smartdb {
namespace Ast {

class Select : public Node {
public:
  Select();
  virtual ~Select();

  // [TODO] - Define operator new, delete, which creates/deletes object in free list (like mem_root in mysql)
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_SELECT_H_ */
