/*
 * Record.h
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_RECORD_H_
#define LIB_DATASTRUCT_RECORD_H_

#include "datastruct/Buffer.h"

namespace Smartdb {

class Record {
public:
  Record(Buffer &buf);
  virtual ~Record();

  Buffer buf;

private:
  Record();
};

int hello();

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_RECORD_H_ */
