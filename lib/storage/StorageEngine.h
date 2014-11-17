/*
 * StorageEngine.h
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_STORAGE_STORAGEENGINE_H_
#define INCLUDE_STORAGE_STORAGEENGINE_H_

#include "api/SmartdbType.h"
#include "datastruct/Records.h"

namespace Smartdb {

class StorageEngine {
public:
  virtual ~StorageEngine() {}

  virtual SmartdbErr read_records(Records &records, size_t n_records) = 0;
};

} /* namespace Smartdb */

#endif /* INCLUDE_STORAGE_STORAGEENGINE_H_ */
