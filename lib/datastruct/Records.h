/*
 * Records.h
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_RECORDS_H_
#define LIB_DATASTRUCT_RECORDS_H_

#include <vector>
#include "datastruct/ColumnDef.h"
#include "datastruct/Column.h"
#include "mem/Buffer.h"
#include "hack/Class.h"

namespace Smartdb {

// Records are set of Column
class Records {
public:
  Records(const std::vector<const ColumnDef *>& coldefs,
          const std::vector<Buffer *>& colbufs);
  ~Records();

  size_t size() const;
  void clear();

  const std::vector<const ColumnDef *> &coldefs;
  std::vector<Column *> columns;

private:
  const std::vector<Buffer *> &colbufs;
  size_t _size;

  PREVENT_CLASS_DEFAULT_METHODS(Records)
};


inline
size_t Records::size() const {
  return _size;
}

inline
void Records::clear() {
  for (size_t i = 0; i < columns.size(); ++i) columns[i]->clear();
}

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_RECORDS_H_ */
