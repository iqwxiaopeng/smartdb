/*
 * Root.cpp
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#include "ast/SelectStatement.hpp"

namespace Smartdb {
namespace Ast {

SelectStatement::SelectStatement()
: select_list_all(false)
{
}

SelectStatement::~SelectStatement() {
}

}
}
