/*
 * Column.h
 *
 *  Created on: 2014/11/16
 *      Author: nakatani.sho
 */

#ifndef LIB_DATASTRUCT_FIXEDLENGTHCOLUMN_H_
#define LIB_DATASTRUCT_FIXEDLENGTHCOLUMN_H_

#include "datastruct/Buffer.h"
#include "hack/Class.h"
#include "hack/Assert.h"

namespace Smartdb {

template<typename T>
class FixedLengthColumn {
public:
  FixedLengthColumn(Buffer &buf);
  virtual ~FixedLengthColumn();

  SmartdbErr add(T val);
  T get(size_t row_index) const;

  Buffer &buf;

private:
  size_t filled_row;

  PREVENT_CLASS_DEFAULT_METHODS(FixedLengthColumn);
};


template<typename T>
FixedLengthColumn<T>::FixedLengthColumn(Buffer& buf)
: filled_row(0), buf(buf)
{
}

template<typename T>
FixedLengthColumn<T>::~FixedLengthColumn() {
  // TODO Auto-generated destructor stub
}

template<typename T>
inline
SmartdbErr FixedLengthColumn<T>::add(T val) {
  if ((filled_row + 1) * sizeof(T) > buf.size())
    return MEM_BUF_SHORTAGE;

  *((T *)(buf.ptr() + (filled_row * sizeof(T)))) = val;
  filled_row++;

  return NO_ERR;
}

template<typename T>
inline
T FixedLengthColumn<T>::get(size_t row_index) const {
  ASSERT(row_index < filled_row);
  return *((T *)(this->buf.ptr() + (row_index * sizeof(T))));
}

} /* namespace Smartdb */

#endif /* LIB_DATASTRUCT_FIXEDLENGTHCOLUMN_H_ */
