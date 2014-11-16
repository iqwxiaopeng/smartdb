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
  Buffer();
  virtual ~Buffer();

  SmartdbErr allocate(size_t size);
  SmartdbErr reallocate(size_t size);
  void deallocate();  // reentrant

private:
  char *_ptr;
  size_t _size;

public:
  char *ptr() const;
  size_t size() const;

  PREVENT_COPY_CONSTRUCTOR(Buffer);
  PREVENT_OBJECT_ASSIGNMENT(Buffer);
};

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_BUFFER_H_ */
