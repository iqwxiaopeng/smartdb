/*
 * ColumnDef.h
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_COLUMNDEF_H_
#define LIB_DATASTRUCT_COLUMNDEF_H_

#include <string>
#include "api/SmartdbType.hpp"
#include "hack/Class.hpp"

namespace Smartdb {

class ColumnDef {
public:
  ColumnDef(std::string name, SmartdbType type);
  virtual ~ColumnDef();

  size_t size() const;

  std::string name;
  SmartdbType type;

  PREVENT_CLASS_DEFAULT_METHODS(ColumnDef);
};


inline
size_t ColumnDef::size() const {
  switch (type) {
  case SMARTDB_INT: return sizeof(SmartdbInt);
  case SMARTDB_DOUBLE: return sizeof(SmartdbDouble);
  default: abort(); return -1;
  }
}

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_COLUMNDEF_H_ */
