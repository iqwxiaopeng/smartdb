/*
 * Record.h
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_RECORD_H_
#define LIB_DATASTRUCT_RECORD_H_

#include <vector>
#include "datastruct/Buffer.h"
#include "hack/Class.h"

namespace Smartdb {

class Record {
public:
  Record(size_t n_col, Buffer &buf);
  virtual ~Record();

  SmartdbInt get_int(size_t col_index) const;
  SmartdbErr add_int(SmartdbInt val);

  size_t n_col;
  Buffer &buf;

private:
  std::vector<size_t> col_starts_from;
  size_t filled_col;

  PREVENT_CLASS_DEFAULT_METHODS(Record);
};

int hello();

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_RECORD_H_ */
