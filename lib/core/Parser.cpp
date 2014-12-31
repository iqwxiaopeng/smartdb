/*
 * Parser.cpp
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#include "core/Parser.hpp"
#include "ast/Root.hpp"
#include "parser/Interface.hpp"
#include "err/ParseError.hpp"

namespace Smartdb {

const char * Parser::sql = 0;

Parser::Parser(const char* const sql)
: ast_root(0)
{
  Parser::sql = sql;
  ast_root = parse();
}

Parser::~Parser() {
  if (ast_root) delete ast_root;  // each Node of Ast is deleted at a time
}

const Ast::Root* Parser::parse() {
  void * buf = smartdb_reg_parsed_str(Parser::sql);
  int ret = smartdb_parse();
  smartdb_delete_parse_buf(buf);
  if (ret != 0) {
    // after yyerror() is called
    throw ParseError(sql);
  }
  return Ast::Root::ast_root;
}


} /* namespace Smartdb */
