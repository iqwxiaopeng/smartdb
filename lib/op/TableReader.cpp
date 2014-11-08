#include "TableReader.h"

namespace Smartdb {

void TableReader::read() {
  ssize_t ret = 1;
  while (ret > 0) {
    RecordQueue records = RecordQueue(size);
    ret = read_records(this->storage, records);
    this->out_queue.register_records(records);
  }
}

}
