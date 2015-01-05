/*
 * Records.h
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_RECORDS_H_
#define LIB_DATASTRUCT_RECORDS_H_

#include <vector>

#include "storageinterface/Column.hpp"
#include "storageinterface/ColumnDef.hpp"
#include "storageinterface/Buffer.hpp"
#include "hack/Class.hpp"

namespace Smartdb {

// Records are set of Column
class Records {
public:
  /**
   * Construct records, which is sets of Column.
   * @param coldefs
   * @param min_colbuf_sizes Minimum size of each column's buffer.
   */
  Records(const std::vector<const ColumnDef *>& coldefs,
          const std::vector<size_t>& min_colbuf_sizes);
  ~Records();

  size_t size() const;
  void clear();

  const std::vector<const ColumnDef *> &coldefs;
  std::vector<Column *> columns;

  PREVENT_CLASS_DEFAULT_METHODS(Records)
};


inline size_t Records::size() const {
  ASSERT(columns.size() > 0);
  size_t _size = columns[0]->get_n_filled_row();
  for (size_t i = 1; i < columns.size(); ++i)
    ASSERT(columns[i]->get_n_filled_row() == _size)

  return _size;
}

inline
void Records::clear() {
  for (size_t i = 0; i < columns.size(); ++i) columns[i]->clear();
}

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_RECORDS_H_ */
