/*
 * Column.h
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_COLUMN_H_
#define LIB_DATASTRUCT_COLUMN_H_

#include "ColumnDef.h"
#include "hack/Assert.h"

namespace Smartdb {

class Column {
public:
  virtual ~Column() {}

  virtual SmartdbErr add(const SmartdbValue &val) = 0;
  virtual SmartdbValue get(size_t row_index) const = 0;
  virtual void clear() = 0;

  // [TODO] - Bulk add/get for performance
};

}

#endif /* LIB_DATASTRUCT_COLUMN_H_ */
