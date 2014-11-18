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
  virtual ~Records();

  const std::vector<const ColumnDef *> &coldefs;
  std::vector<Column *> columns;

private:
  const std::vector<Buffer *> &colbufs;

  PREVENT_CLASS_DEFAULT_METHODS(Records)
};

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_RECORDS_H_ */
