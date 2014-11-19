/*
 * ColumnDef.h
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_COLUMNDEF_H_
#define LIB_DATASTRUCT_COLUMNDEF_H_

#include <string>
#include "api/SmartdbType.h"
#include "hack/Class.h"

namespace Smartdb {

class ColumnDef {
public:
  ColumnDef(std::string name, SmartdbType type);
  virtual ~ColumnDef();

  std::string name;
  SmartdbType type;

  PREVENT_CLASS_DEFAULT_METHODS(ColumnDef);
};

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_COLUMNDEF_H_ */
