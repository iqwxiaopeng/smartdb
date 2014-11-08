/*
 * Buffer.h
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_BUFFER_H_
#define LIB_DATASTRUCT_BUFFER_H_

#include "api/SmartdbType.h"
#include "hack/Class.h"

namespace Smartdb {

class Buffer {
public:
  Buffer(size_t size);
  virtual ~Buffer();

  char *ptr;
  size_t size;

  PREVENT_CLASS_DEFAULT_METHODS(Buffer);
};

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_BUFFER_H_ */
