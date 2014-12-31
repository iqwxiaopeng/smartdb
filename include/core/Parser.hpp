/*
 * Parser.h
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_CORE_PARSER_H_
#define INCLUDE_CORE_PARSER_H_

#include "hack/Class.hpp"

namespace Smartdb {

namespace Ast {
class Root;
}

class Parser {
public:
  static const char * sql;

  Parser(const char * const sql);
  virtual ~Parser();

private:
  const Ast::Root * parse();

  const Ast::Root * ast_root;

  PREVENT_CLASS_DEFAULT_METHODS(Parser);
};

} /* namespace Smartdb */

#endif /* INCLUDE_CORE_PARSER_H_ */
