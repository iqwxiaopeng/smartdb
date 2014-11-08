/*
 * Record.cpp
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#include "Record.h"

namespace Smartdb {

Record::Record(Buffer& buf)
: buf(buf)
{
}

Record::~Record() {
  // TODO Auto-generated destructor stub
}

  int hello() {
    return 777;
  }

} /* namespace Smartdb */
