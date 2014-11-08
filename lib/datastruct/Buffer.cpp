/*
 * Buffer.cpp
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#include "Buffer.h"

namespace Smartdb {

Buffer::Buffer(size_t size)
: size(size)
{
  this->ptr = new char[size];
}

Buffer::~Buffer() {
  delete[] this->ptr;
}

} /* namespace Smartdb */
