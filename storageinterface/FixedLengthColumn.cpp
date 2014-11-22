/*
 * Column.cpp
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#include "storageinterface/FixedLengthColumn.h"
#include "api/SmartdbType.h"
#include "hack/Assert.h"

#define ADD_TO_BUF(type) \
{ \
  if ((filled_row + 1) * sizeof(type) > buf.size()) \
    return MEM_BUF_SHORTAGE; \
  *((type *)(buf.ptr() + (filled_row * sizeof(type)))) = val.v_##type; \
}

#define GET_FROM_BUF(type) \
{ val.v_##type = *((type *)(this->buf.ptr() + (row_index * sizeof(type)))); }


namespace Smartdb {

FixedLengthColumn::FixedLengthColumn(const ColumnDef &coldef, Buffer& buf)
: coldef(coldef), buf(buf), filled_row(0)
{
}

FixedLengthColumn::~FixedLengthColumn() {
  // TODO Auto-generated destructor stub
}

inline
SmartdbErr FixedLengthColumn::add(const SmartdbValue& val) {
  switch (coldef.type) {
  case SMARTDB_INT:
    ADD_TO_BUF(SmartdbInt)
    break;
  case SMARTDB_DOUBLE:
    ADD_TO_BUF(SmartdbDouble)
    break;
  default:
    ASSERT(false);
  }

  filled_row++;
  return NO_ERR;
}

inline
SmartdbValue FixedLengthColumn::get(size_t row_index) const {
  ASSERT(row_index < filled_row);

  SmartdbValue val;

  switch (coldef.type) {
  case SMARTDB_INT:
    GET_FROM_BUF(SmartdbInt);
    break;
  case SMARTDB_DOUBLE:
    GET_FROM_BUF(SmartdbDouble);
    break;
  default:
    ASSERT(false);
  }
  return val;
}

inline
size_t FixedLengthColumn::size() const {
  return filled_row;
}

inline
void FixedLengthColumn::clear() {
  filled_row = 0;
}

} /* namespace Smartdb */
