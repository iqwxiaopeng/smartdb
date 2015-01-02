/*
 * Buffer.cpp
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#include <cstdlib>
#include "storageinterface/Buffer.hpp"
#include "hack/Assert.hpp"
#include "hack/Error.hpp"
#include "api/SmartdbType.hpp"

namespace Smartdb {

Buffer::Buffer(size_t size)
: _ptr(NULL), _size(size)
{
  ASSERT(size > 0);
  allocate();
}

Buffer::~Buffer() {
  deallocate();
}

void Buffer::extend(size_t ratio) throw(AllocError)
{
  ASSERT(ratio > 1);
}

// Customize this function and deallocate() to implement *better* allocation
void Buffer::allocate() throw(AllocError) {
#if SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)
  ASSERT(_size < 64 * 1024 * 1024);  // [TODO] - 64MB is too large to malloc(3). See http://blog.kazuhooku.com/2014/12/64-bit.html
  ASSERT(!_ptr);
  if (!(_ptr = (char *)std::malloc(_size))) STRERROR_THROW(AllocError, "malloc failed");
#endif // SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)
}

void Buffer::reallocate(size_t new_size) throw(AllocError) {
#if SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)
  ASSERT(_ptr);
  ASSERT(new_size > _size);
  if (!(_ptr = (char *)std::realloc(_ptr, _size))) STRERROR_THROW(AllocError, "realloc failed");
#endif // SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)
}

void Buffer::deallocate() {
#if SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)
  if (_ptr) std::free(_ptr);
#endif // SMARTDB_MEM_MANAGER == Default || !defined(SMARTDB_MEM_MANAGER)
}

} /* namespace Smartdb */
