/*
 * SelectList.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_SELECTLIST_H_
#define INCLUDE_AST_SELECTLIST_H_

#include <vector>
#include <string>
#include "Node.h"

namespace Smartdb {
namespace Ast {

class SelectList : public Node {
public:
  SelectList();
  virtual ~SelectList();

  std::vector<std::string> columns;
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_SELECTLIST_H_ */
