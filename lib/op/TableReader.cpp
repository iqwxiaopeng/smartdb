#include <stdlib.h>
#include "op/TableReader.h"
#include "datastruct/Records.h"
#include "hack/DynamicLib.h"
#include "log/Logger.h"

#define LOAD_FUNC(func_name) \
  if (!(storage_funcs.func_name = \
        (func_name ## _t)load_func(dlib_handler, #func_name))) { \
    logger->error(::dlerror()); \
    abort(); \
  }


namespace Smartdb {

TableReader::TableReader(const std::string& storage_engine_name)
: storage_engine_name(storage_engine_name), dlib_handler(0)
{
  load_dlib_funcs();
}

TableReader::~TableReader() {
  unload_dlib_funcs();
}

SmartdbErr TableReader::run() {
  return read();
}

SmartdbErr TableReader::read() {
/*  extra["path"] = "fixture/storage_csv_normal.csv";
    EXPECT_EQ((void *)NO_ERR, storage_init(&logger, extra));

    const ColumnDef coldef1("col1", SMARTDB_INT);
    const ColumnDef coldef2("col2", SMARTDB_INT);
    std::vector<const ColumnDef *> coldefs(2, NULL);
    coldefs[0] = &coldef1;
    coldefs[1] = &coldef2;

    Buffer colbuf1(1024);
    Buffer colbuf2(1024);
    std::vector<Buffer *> colbufs(2, NULL);
    colbufs[0] = &colbuf1;
    colbufs[1] = &colbuf2;

    Records records(coldefs, colbufs);


    //  ssize_t ret = 1;
//  while (ret > 0) {
//    ret = this->storage.read_records(out_records, 1000);
//  }*/
  return NO_ERR;
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
  LOAD_FUNC(storage_init);
  LOAD_FUNC(storage_read_records);
  LOAD_FUNC(storage_finish);
}

inline
void TableReader::unload_dlib_funcs() {
  unload_dlib(dlib_handler);
}

}
