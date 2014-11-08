/*
 * MallocMemoryManager.cpp
 *
 *  Created on: 2014/11/06
 *      Author: nakatani.sho
 */

#include <stdlib.h>
#include "MallocMemoryManager.h"

namespace Smartdb {

MallocMemoryManager::MallocMemoryManager() {
  // TODO Auto-generated constructor stub
}

MallocMemoryManager::~MallocMemoryManager() {
  // TODO Auto-generated destructor stub
}

inline
void* MallocMemoryManager::allocate(size_t size_byte) {
  return malloc(size_byte);
}

inline
void MallocMemoryManager::deallocate(void* ptr) {
  free(ptr);
}

} /* namespace Smartdb */
