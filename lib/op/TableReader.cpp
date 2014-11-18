#include "op/TableReader.h"
#include "datastruct/Records.h"
#include "hack/DynamicLib.h"

namespace Smartdb {

TableReader::TableReader(const std::string& storage_engine_name)
: storage_engine_name(storage_engine_name), lib_handler(0)
{
/*
  lib_t hMyLib = 0;
  hello_t hello = 0;

  if (!(hMyLib = ::MyLoadLib((std::string("/Users/nakatani.sho/tmp/lib") + engine + std::string(".dylib")).c_str()))) { std::cout << dlerror(); abort();
  }
  if (!(hello = (hello_t)::MyLoadProc(hMyLib, "Smartdb::hello"))) {  }

hello(); */
}

void TableReader::read() {
//  ssize_t ret = 1;
//  while (ret > 0) {
//    ret = this->storage.read_records(out_records, 1000 /* 行 */);
//  }
}

}
