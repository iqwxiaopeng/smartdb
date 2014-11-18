#include <stdlib.h>
#include "op/TableReader.h"
#include "datastruct/Records.h"
#include "hack/DynamicLib.h"
#include "log/Logger.h"

namespace Smartdb {

TableReader::TableReader(const std::string& storage_engine_name)
: storage_engine_name(storage_engine_name), dlib_handler(0)
{
  load_dlib_funcs();
}

TableReader::~TableReader() {
  unload_dlib_funcs();
}

void TableReader::read() {
//  ssize_t ret = 1;
//  while (ret > 0) {
//    ret = this->storage.read_records(out_records, 1000 /* 行 */);
//  }
}

inline
std::string TableReader::dlib_name() {
  return std::string("lib") + storage_engine_name + std::string(".so");
}

inline
void TableReader::load_dlib_funcs() {
  if (!(dlib_handler = load_dlib(dlib_name().c_str()))) {
    logger->error(::dlerror());
    abort();
  }
  if (!(storage_funcs.storage_init =
        (storage_init_t)load_func(dlib_handler, "storage_init"))) {
    logger->error(::dlerror());
    abort();
  }
  if (!(storage_funcs.storage_read_records =
        (storage_read_records_t)load_func(dlib_handler, "storage_read_records"))) {
    logger->error(::dlerror());
    abort();
  }
}

inline
void TableReader::unload_dlib_funcs() {
  unload_dlib(dlib_handler);
}

}
