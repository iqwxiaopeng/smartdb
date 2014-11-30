/*
 * Interface.cpp
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#include "parser/Interface.h"

extern
int yyparse();

namespace Smartdb {

bool smartdb_parse() {
  return ::yyparse();
}

}

