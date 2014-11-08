/*
 * MemoryManager.h
 *
 *  Created on: 2014/11/06
 *      Author: nakatani.sho
 */

#ifndef LIB_CORE_MEMORYMANAGER_H_
#define LIB_CORE_MEMORYMANAGER_H_

namespace Smartdb {

class MemoryManager {
public:
  MemoryManager();
  virtual ~MemoryManager();

  virtual void *allocate(size_t size_byte) = 0;
  virtual void deallocate(void *ptr) = 0;
};

} /* namespace Smartdb */

#endif /* LIB_CORE_MEMORYMANAGER_H_ */
