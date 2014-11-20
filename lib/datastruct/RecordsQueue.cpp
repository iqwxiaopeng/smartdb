/*
 * RecordsQueue.cpp
 *
 *  Created on: 2014/11/20
 *      Author: nakatani.sho
 */

#include "RecordsQueue.h"

namespace Smartdb {

RecordsQueue::RecordsQueue()
: _finished(false)
{
}

RecordsQueue::~RecordsQueue() {
  // TODO Auto-generated destructor stub
}

void RecordsQueue::push(const Records * const records) {
  q.push(records);
}

void RecordsQueue::pop() {
  q.pop();
}

const Records * RecordsQueue::front() const {
  if (q.empty()) return NULL;
  return q.front();
}


} /* namespace Smartdb */
