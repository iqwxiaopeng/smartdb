/*
 * Interface.cpp
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#include "parser/Interface.hpp"

extern int yyparse();
extern "C" void * yy_scan_string(const char *);
extern "C" void yy_delete_buffer(void *);

namespace Smartdb {

int smartdb_parse() {
  return ::yyparse();
}

void * smartdb_reg_parsed_str(const char * str) {
  return ::yy_scan_string(str);
}

void smartdb_delete_parse_buf(void* buf) {
  ::yy_delete_buffer(buf);
}

}
