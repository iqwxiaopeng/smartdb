/*
 * Column.h
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_FIXEDLENGTHCOLUMN_H_
#define LIB_DATASTRUCT_FIXEDLENGTHCOLUMN_H_

#include "storageinterface/Column.hpp"
#include "api/SmartdbType.hpp"
#include "err/AllocError.hpp"
#include "storageinterface/Buffer.hpp"
#include "hack/Class.hpp"

namespace Smartdb {

/**
 * FixedLengthColumn represents partial column (not including all records).
 *
 * All elements have the same type, which has fixed-length (4-byte, 8-byte, ...).
 */
class FixedLengthColumn : public Column {
public:
  /**
   * Constructor.
   * @param coldef
   * @param min_n_rows At least \p min_n_rows * \p coldef.size() bytes are allocated.
   *   add() will automatically extend allocated memory.
   * @throw Smartdb::AllocError when failed to allocate memory.
   */
  FixedLengthColumn(const ColumnDef & coldef, size_t min_n_rows = DEFAULT_MIN_N_ROWS) throw(AllocError);

  ~FixedLengthColumn();

  /**
   * Add a value to this column.
   * @param val
   * @throw Smartdb::AllocError when failed to extend memory.
   */
  void add(const SmartdbValue &val) throw(AllocError);

  SmartdbValue get(size_t row_index) const;

  size_t get_n_filled_row() const { return n_filled_row; }

  void clear() { n_filled_row = 0; }

  Buffer buf;

private:
  static const size_t DEFAULT_MIN_N_ROWS = 1024;
  size_t n_filled_row;

  PREVENT_CLASS_DEFAULT_METHODS(FixedLengthColumn);
};

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_FIXEDLENGTHCOLUMN_H_ */
