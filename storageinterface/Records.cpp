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
  const std::vector<size_t>& min_n_rows)
: coldefs(coldefs), columns(coldefs.size(), 0)
{
  for (size_t i = 0; i < coldefs.size(); ++i) {
    if (IS_FIXED_LENGTH_TYPE(coldefs[i]->type))
      columns[i] = new FixedLengthColumn(*coldefs[i], min_n_rows[i]);
    else
      NOT_IMPLEMENTED;
  }
}

Records::~Records() {
  for (size_t i = 0; i < coldefs.size(); ++i) delete columns[i];
}

} /* namespace Smartdb */
