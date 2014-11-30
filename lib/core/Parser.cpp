/*
 * Parser.cpp
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#include "core/Parser.h"
#include "ast/Root.h"
#include "parser/Interface.h"

namespace Smartdb {

const char * Parser::sql = 0;

Parser::Parser(const char* const sql)
: root_ast(0)
{
  Parser::sql = sql;
  root_ast = parse();
}

Parser::~Parser() {
  if (root_ast) delete root_ast;  // each Node of Ast is deleted at a time
}

const Ast::Root* Parser::parse() {
  if (!smartdb_parse()) {
    // after yyerror() is called
    // [TODO] - throw ParseError(sql);
  }
  return Ast::Root::ast_root;
}


} /* namespace Smartdb */
