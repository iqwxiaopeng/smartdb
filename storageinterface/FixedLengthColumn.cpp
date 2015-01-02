/*
 * Column.cpp
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#include "storageinterface/FixedLengthColumn.hpp"
#include "api/SmartdbType.hpp"
#include "hack/Assert.hpp"

#define ADD_TO_BUF(type) \
{ \
  *((type *)(buf.ptr() + (n_filled_row * sizeof(type)))) = val.v_##type; \
}

#define GET_FROM_BUF(type) \
{ val.v_##type = *((type *)(this->buf.ptr() + (row_index * sizeof(type)))); }


namespace Smartdb {

FixedLengthColumn::FixedLengthColumn(const ColumnDef &coldef, size_t min_n_rows) throw(AllocError)
: coldef(coldef), buf(min_n_rows), n_filled_row(0)
{
}

FixedLengthColumn::~FixedLengthColumn() {
  // TODO Auto-generated destructor stub
}

inline void FixedLengthColumn::add(const SmartdbValue& val) throw(AllocError) {
  switch (coldef.type) {
  case SMARTDB_INT:
    if ((n_filled_row + 1) * sizeof(SmartdbDouble) > buf.size()) buf.extend();
    ADD_TO_BUF(SmartdbInt)
    break;
  case SMARTDB_DOUBLE:
    if ((n_filled_row + 1) * sizeof(SmartdbDouble) > buf.size()) buf.extend();
    ADD_TO_BUF(SmartdbDouble)
    break;
  default:
    ASSERT(false);
  }
  n_filled_row++;
}

inline SmartdbValue FixedLengthColumn::get(size_t row_index) const {
  ASSERT(row_index < n_filled_row);

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

inline size_t FixedLengthColumn::get_n_filled_row() const {
  return n_filled_row;
}

inline
void FixedLengthColumn::clear() {
  n_filled_row = 0;
}

} /* namespace Smartdb */
