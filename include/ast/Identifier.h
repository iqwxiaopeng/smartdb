/*
 * Identifier.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_IDENTIFIER_H_
#define INCLUDE_AST_IDENTIFIER_H_

#include <string>
#include "Node.h"

namespace Smartdb {
namespace Ast {

class Identifier : public Node {
public:
  Identifier();
  virtual ~Identifier();

  std::string name;
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_IDENTIFIER_H_ */
