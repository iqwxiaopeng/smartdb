/*
 * Csv.h
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#ifndef LIB_STORAGE_CSV_H_
#define LIB_STORAGE_CSV_H_

#include "api/Smartdb.h"
#include "hack/Class.h"

namespace Smartdb {



class Csv : public StorageEngine {
public:
  Csv();
  virtual ~Csv();

  SmartdbErr smartdb_read_records(Records &records, size_t n_records);

private:
  Buffer read_buf;

  PREVENT_COPY_CONSTRUCTOR(Csv);
  PREVENT_OBJECT_ASSIGNMENT(Csv);
};

} /* namespace Smartdb */

#endif /* LIB_STORAGE_CSV_H_ */
