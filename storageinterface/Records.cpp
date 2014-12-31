/*
 * Records.cpp
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#include "storageinterface/Records.hpp"
#include "storageinterface/FixedLengthColumn.hpp"
#include "hack/Assert.hpp"

namespace Smartdb {

Records::Records(
  const std::vector<const ColumnDef *>& coldefs,
  const std::vector<size_t>& colbuf_sizes)
: coldefs(coldefs), columns(coldefs.size(), 0), colbufs(coldefs.size(), 0)
{
  for (size_t i = 0; i < coldefs.size(); ++i) {
    colbufs[i] = new Buffer(colbuf_sizes[i]);
    columns[i] = new FixedLengthColumn(*coldefs[i], *colbufs[i]);
  }
}

Records::~Records() {
  for (size_t i = 0; i < coldefs.size(); ++i) {
    delete columns[i];
    delete colbufs[i];
  }
}

} /* namespace Smartdb */
