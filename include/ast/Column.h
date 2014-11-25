/*
 * Column.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_COLUMN_H_
#define INCLUDE_AST_COLUMN_H_

#include <string>
#include "Identifier.h"

namespace Smartdb {
namespace Ast {

class Column : public Identifier {
public:
  Column();
  virtual ~Column();

  std::string name;
};

} /* namespace Ast */
} /* namespace Smartdb */

#endif /* INCLUDE_AST_COLUMN_H_ */
