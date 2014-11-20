/*
 * RecordsQueue.h
 *
 *  Created on: 2014/11/20
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_RECORDSQUEUE_H_
#define LIB_DATASTRUCT_RECORDSQUEUE_H_

#include <queue>
#include "Records.h"
#include "hack/Class.h"

namespace Smartdb {

class RecordsQueue {
public:
  RecordsQueue();
  virtual ~RecordsQueue();

  void push(const Records * records);
  void pop();
  const Records * const front() const;  // NULL when empty
  void finish() { _finished = true; }
  bool finished() { return _finished; }

private:
  std::queue<const Records *> q;
  bool _finished;

  PREVENT_COPY_CONSTRUCTOR(RecordsQueue);
  PREVENT_OBJECT_ASSIGNMENT(RecordsQueue);
};

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_RECORDSQUEUE_H_ */
