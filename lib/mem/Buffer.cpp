/*
 * Buffer.cpp
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#include "Buffer.h"
#include "hack/Assert.h"
#include "api/SmartdbType.h"

namespace Smartdb {

Buffer::Buffer(size_t size)
: _ptr(NULL), _size(size)
{
  allocate();
}

Buffer::~Buffer() {
  deallocate();
}

// Customize this function and deallocate() to implement *better* allocation
void Buffer::allocate() BUFFER_ALLOCATE_THROW {
#if SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)
  ASSERT(!_ptr);
  _ptr = new char[_size];
#endif // SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)
}

void Buffer::deallocate() {
#if SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)
  if (_ptr) delete[] _ptr;
#endif // SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)
}

} /* namespace Smartdb */
