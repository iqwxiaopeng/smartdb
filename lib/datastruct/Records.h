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
#include "Column.h"
#include "mem/Buffer.h"
#include "hack/Class.h"

namespace Smartdb {

// Records are set of Column
class Records {
public:
  Records(const std::vector<const ColumnDef * const>& coldefs,
          std::vector<Column *>& columns,
          const std::vector<Buffer * const>& colbufs);
  virtual ~Records();

  const std::vector<const ColumnDef * const> &coldefs;
  std::vector<Column *> &columns;

private:
  const std::vector<Buffer * const> &colbufs;

  PREVENT_CLASS_DEFAULT_METHODS(Records)
};

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_RECORDS_H_ */
