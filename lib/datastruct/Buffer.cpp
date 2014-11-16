/*
 * Buffer.cpp
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#include "Buffer.h"
#include "hack/Assert.h"
#include "api/SmartdbType.h"
#include "core/Singleton.h"

namespace Smartdb {

Buffer::Buffer()
: _ptr(NULL), _size(0)
{
}

Buffer::~Buffer() {
  deallocate();
}

SmartdbErr Buffer::allocate(size_t size) {
  ASSERT(!_ptr);
  _ptr = (char *)Singleton::mm.allocate(size);
  _size = size;
  if (!_ptr) return PHYSICAL_MEM_SHORTAGE;
  return NO_ERR;
}

SmartdbErr Buffer::reallocate(size_t size) {
  ASSERT(_ptr);
  char *ret = (char *)Singleton::mm.reallocate(_ptr, size);
  if (!ret) return PHYSICAL_MEM_SHORTAGE;

  _ptr = ret;
  _size = size;
  return NO_ERR;
}

void Buffer::deallocate() {
  if (_ptr) Singleton::mm.deallocate(_ptr);
}

char* Buffer::ptr() const {
  ASSERT(_ptr);
  return _ptr;
}

size_t Buffer::size() const {
  ASSERT(_ptr);
  return _size;
}

} /* namespace Smartdb */
