/*
 * Record.cpp
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#include <assert.h>
#include "Record.h"

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
  assert(col_index < n_col);

  size_t starts_from = this->col_starts_from[col_index];
  SmartdbInt aaa = *((SmartdbInt *)(this->buf.ptr + starts_from));;
  return *((SmartdbInt *)(this->buf.ptr + starts_from));
}

SmartdbErr Record::add_int(SmartdbInt val) {
  assert(filled_col < n_col);

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
