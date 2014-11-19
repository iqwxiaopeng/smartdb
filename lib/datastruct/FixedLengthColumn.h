/*
 * Column.h
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_FIXEDLENGTHCOLUMN_H_
#define LIB_DATASTRUCT_FIXEDLENGTHCOLUMN_H_

#include "Column.h"
#include "api/SmartdbType.h"
#include "ColumnDef.h"
#include "mem/Buffer.h"
#include "hack/Class.h"

namespace Smartdb {

// FixedLengthColumn represents partial column (not including all records)
class FixedLengthColumn : public Column {
public:
  FixedLengthColumn(const ColumnDef &coldef, Buffer &buf);
  ~FixedLengthColumn();

  SmartdbErr add(const SmartdbValue &val);
  SmartdbValue get(size_t row_index) const;
  void clear();

  const ColumnDef &coldef;
  Buffer &buf;

private:
  size_t filled_row;

  PREVENT_CLASS_DEFAULT_METHODS(FixedLengthColumn);
};

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_FIXEDLENGTHCOLUMN_H_ */
