/*
 * Records.h
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_RECORDS_H_
#define LIB_DATASTRUCT_RECORDS_H_

#include <vector>
#include "storageinterface/ColumnDef.h"
#include "storageinterface/Column.h"
#include "storageinterface/Buffer.h"
#include "hack/Class.h"

namespace Smartdb {

// Records are set of Column
class Records {
public:
  Records(const std::vector<const ColumnDef *>& coldefs,
          const std::vector<size_t>& colbuf_sizes);
  ~Records();

  size_t size() const;
  void clear();

  const std::vector<const ColumnDef *> &coldefs;
  std::vector<Column *> columns;

private:
  std::vector<Buffer *> colbufs;

  PREVENT_CLASS_DEFAULT_METHODS(Records)
};


inline
size_t Records::size() const {
  ASSERT(columns.size() > 0);
  size_t _size = columns[0]->size();
  for (size_t i = 1; i < columns.size(); ++i)
    ASSERT(columns[i]->size() == _size)

  return _size;
}

inline
void Records::clear() {
  for (size_t i = 0; i < columns.size(); ++i) columns[i]->clear();
}

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_RECORDS_H_ */
