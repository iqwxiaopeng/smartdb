/*
 * Record.cpp
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#include "Record.h"
#include "hack/Assert.h"

namespace Smartdb {

Record::Record(size_t n_col, Buffer& buf)
: n_col(n_col), col_starts_from(std::vector<size_t>(n_col, 0)), filled_col(0),
  buf(buf)
{
}

Record::~Record() {
  // TODO Auto-generated destructor stub
}

SmartdbInt Record::get_int(size_t col_index) const {
  ASSERT(col_index < n_col);

  size_t starts_from = this->col_starts_from[col_index];
  return *((SmartdbInt *)(this->buf.ptr + starts_from));
}

SmartdbErr Record::add_int(SmartdbInt val) {
  ASSERT(filled_col < n_col);

  if (col_starts_from[filled_col] + sizeof(SmartdbInt) > buf.size)
    return MEM_BUF_SHORTAGE;

  size_t starts_from = this->col_starts_from[this->filled_col];

  this->filled_col++;
  if (this->filled_col < this->n_col)
    this->col_starts_from[this->filled_col] = sizeof(SmartdbInt);

  *((SmartdbInt *)(this->buf.ptr + starts_from)) = val;

  return NO_ERR;
}

int hello() {
    return 777;
  }

} /* namespace Smartdb */
