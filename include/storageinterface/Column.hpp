/*
 * Column.h
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_COLUMN_H_
#define LIB_DATASTRUCT_COLUMN_H_

#include "storageinterface/ColumnDef.hpp"
#include "hack/Assert.hpp"

namespace Smartdb {

/**
 * Abstract base class of FixedLengthColumn and VarLengthColumn.
 */
class Column {
public:
  static const size_t DEFAULT_MIN_N_ROWS = 1024;

  Column(const ColumnDef & coldef) : coldef(coldef) {}
  virtual ~Column() {}

  /**
   * Return the name of column.
   */
  const std::string & get_name() const { return coldef.name; }

  /**
   * Return the type enum of column.
   */
  const SmartdbType get_type() const { return coldef.type; }

  virtual size_t get_n_filled_row() const = 0;
  virtual void clear() = 0;

  virtual void add(const SmartdbValue &val) = 0;
  virtual SmartdbValue get(size_t row_index) const = 0;

  // [TODO] - Bulk add/get for performance

protected:
  const ColumnDef & coldef;
};

}

#endif /* LIB_DATASTRUCT_COLUMN_H_ */
