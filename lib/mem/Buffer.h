/*
 * Buffer.h
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_BUFFER_H_
#define LIB_DATASTRUCT_BUFFER_H_

#if SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)
#include <new>
#define __THROW throw(std::bad_alloc)
#endif // SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)

#include "api/SmartdbType.h"
#include "hack/Class.h"
#include "hack/Assert.h"

namespace Smartdb {

class Buffer {
public:
  Buffer(size_t size);
  virtual ~Buffer();

private:
  void allocate() __THROW;
  void deallocate();

public:
  char * const ptr() const;
  size_t size() const;

private:
  char *_ptr;
  size_t _size;

PREVENT_CLASS_DEFAULT_METHODS(Buffer);
};


inline
char * const Buffer::ptr() const {
  ASSERT(_ptr);
  return _ptr;
}

inline
size_t Buffer::size() const {
  ASSERT(_ptr);
  return _size;
}


} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_BUFFER_H_ */
