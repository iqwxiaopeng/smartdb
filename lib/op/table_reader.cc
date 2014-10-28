#include "table_reader.h"

namespace Smartdb {

void TableReader::read() {
  ssize_t ret = 1;
  while (ret > 0) {
    Records* records = new Records(size);
    ret = read_records(this->storage, records);
    out_queue.register_buffer(records);
  }
}

}