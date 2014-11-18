#include <stdlib.h>
#include "op/TableReader.h"
#include "datastruct/Records.h"
#include "hack/DynamicLib.h"
#include "log/Logger.h"

namespace Smartdb {

TableReader::TableReader(const std::string& storage_engine_name)
: storage_engine_name(storage_engine_name), lib_handler(0)
{
  if (!(lib_handler = ::load_dlib(storage_engine_dlib_name().c_str()))) {
    logger->error(dlerror());
    abort();
  }
/*  if (!(hello = (hello_t)::MyLoadProc(hMyLib, "Smartdb::hello"))) {  }

hello();*/
}

void TableReader::read() {
//  ssize_t ret = 1;
//  while (ret > 0) {
//    ret = this->storage.read_records(out_records, 1000 /* 行 */);
//  }
}

inline
std::string TableReader::storage_engine_dlib_name() {
  return std::string("lib") + storage_engine_name + std::string(".so");
}

}
