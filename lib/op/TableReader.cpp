#include <stdlib.h>
#include <stdint.h>
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

TableReader::TableReader(
  const std::vector<const ColumnDef *> &coldefs,
  const std::string& storage_engine_name,
  const std::unordered_map<std::string, std::string> &extra,
  size_t n_records_to_read, size_t buf_size)
: coldefs(coldefs), extra(extra),
  storage_engine_name(storage_engine_name), dlib_handler(0),
  n_records_to_read(n_records_to_read), buf_size(buf_size)
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
  uintptr_t ret;  // hack: functions loaded by dlsym() seem to return void *.
                  // void * => SmartdbErr is prohibited.

  ret = (uintptr_t)storage_funcs.storage_init(logger, extra);
  if (ret != (uintptr_t)NO_ERR) return (SmartdbErr)ret;

  std::vector<Buffer *> colbufs(coldefs.size(), NULL);
  size_t colbuf_size = buf_size / coldefs.size();
  for (size_t i = 0; i < coldefs.size(); ++i)
    colbufs[i] = new Buffer(colbuf_size);

  Records records(coldefs, colbufs);

  size_t read_records = 0;
  bool finished = false;
  while (finished) {
    ret = (uintptr_t)storage_funcs.storage_read_records(
      records, n_records_to_read, read_records, finished);
    if (ret != (uintptr_t)NO_ERR) goto fin;
    out_q.push(&records);
  }

  out_q.finish();
  ret = (uintptr_t)NO_ERR;
fin:
  for (size_t i = 0; i < coldefs.size(); ++i) delete colbufs[i];
  return (SmartdbErr)ret;
}

inline
std::string TableReader::dlib_name_without_suffix() {
  return std::string("lib") + storage_engine_name;
}

inline
void TableReader::load_dlib_funcs() {
  if (!(dlib_handler = load_dlib((dlib_name_without_suffix() + ".so").c_str())))
    logger->info(::dlerror());
  if (!dlib_handler && !(dlib_handler = load_dlib((dlib_name_without_suffix() + ".dylib").c_str())))
    logger->info(::dlerror());
  if (!dlib_handler) {
    logger->error((std::string("Could not load ") + dlib_name_without_suffix() + ". Check if it is in correct library path. e.g. /usr/lib/").c_str());
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
