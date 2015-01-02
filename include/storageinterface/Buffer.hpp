/*
 * Buffer.h
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_BUFFER_H_
#define LIB_DATASTRUCT_BUFFER_H_

#include "err/AllocError.hpp"

#include "api/SmartdbType.hpp"
#include "hack/Class.hpp"
#include "hack/Assert.hpp"

namespace Smartdb {

/**
 * Memory manager.
 * @note Not thread-safe.
 */
class Buffer {
public:
  /**
   * Constructor.
   * @param size Initial buffer size.
   */
  Buffer(size_t size);
  ~Buffer();

  /**
   * Extend memory size \p ratio times.
   * @param ratio Should be greater than 1.
   */
  void extend(size_t ratio = 2) throw(AllocError);

  char * const ptr() const;
  size_t size() const;

private:
  void allocate() throw(AllocError);

  /**
   * Reallocate memory.
   * @param new_size \p new_size must be greater than previous \p _size.
   */
  void reallocate(size_t new_size) throw(AllocError);
  void deallocate();

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
