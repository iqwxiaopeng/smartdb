/*
 * ColumnDef.cpp
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#include "storageinterface/ColumnDef.h"

namespace Smartdb {

ColumnDef::ColumnDef(std::string name, SmartdbType type)
: name(name), type(type)
{
}

ColumnDef::~ColumnDef() {
  // TODO Auto-generated destructor stub
}

} /* namespace Smartdb */
