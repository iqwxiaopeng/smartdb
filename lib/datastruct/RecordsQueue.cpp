/*
 * RecordsQueue.cpp
 *
 *  Created on: 2014/11/20
 *      Author: nakatani.sho
 */

#include "datastruct/RecordsQueue.hpp"

namespace Smartdb {

RecordsQueue::RecordsQueue()
: _finished(false)
{
}

RecordsQueue::~RecordsQueue() {
  // TODO Auto-generated destructor stub
}

void RecordsQueue::push(const Records * records) {
  q.push(records);
}

void RecordsQueue::pop() {
  const Records *r = front();
  if (r) delete r;
  q.pop();
}

size_t RecordsQueue::size() const {
  return q.size();
}

const Records * const RecordsQueue::front() const {
  if (q.empty()) return NULL;
  return q.front();
}


} /* namespace Smartdb */
