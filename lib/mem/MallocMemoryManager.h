/*
 * MallocMemoryManager.h
 *
 *  Created on: 2014/11/06
 *      Author: nakatani.sho
 */

#ifndef LIB_MEM_MALLOCMEMORYMANAGER_H_
#define LIB_MEM_MALLOCMEMORYMANAGER_H_

#include "MemoryManager.h"

namespace Smartdb {

class MallocMemoryManager : public MemoryManager {
public:
  MallocMemoryManager();
  virtual ~MallocMemoryManager();

  virtual void *allocate(size_t size_byte);
  virtual void *reallocate(void *ptr, size_t size_byte);
  virtual void deallocate(void *ptr);
};

} /* namespace Smartdb */

#endif /* LIB_MEM_MALLOCMEMORYMANAGER_H_ */
