/*
 * Records.cpp
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#include "Records.h"
#include "datastruct/FixedLengthColumn.h"
#include "hack/Assert.h"

namespace Smartdb {

Records::Records(
  const std::vector<const ColumnDef * const>& coldefs,
  std::vector<Column *>& columns,
  const std::vector<Buffer * const>& colbufs)
: coldefs(coldefs), columns(columns), colbufs(colbufs)
{
  for (size_t i = 0; i < coldefs.size(); ++i) {
    switch (coldefs[i]->type)
    case SMARTDB_INT: {
      columns[i] = new FixedLengthColumn<SmartdbInt>(*(colbufs[i]));
      break;
    default:
      ASSERT(false);
    }
  }
}

Records::~Records() {
  for (size_t i = 0; i < coldefs.size(); ++i) {
    delete columns[i];
  }
}

} /* namespace Smartdb */
