#include <stdlib.h>
#include <stdint.h>
#include "op/TableReader.h"
#include "storageinterface/Records.h"
#include "hack/DynamicLib.h"
#include "log/Logger.h"

#define LOAD_FUNC(func_name) \
  if (!(storage_funcs.func_name = \
        (func_name ## _t)load_func(dlib_handler, #func_name))) { \
    logger->error(::dlerror()); \
    abort(); \
  }


namespace Smartdb {

extern
Logger *logger;

TableReader::TableReader(
  const std::vector<const ColumnDef *> &coldefs,
  const std::string& storage_engine_name,
  const std::unordered_map<std::string, std::string> &extra,
  size_t n_records_to_read)
: coldefs(coldefs), extra(extra),
  storage_engine_name(storage_engine_name), dlib_handler(0),
  n_records_to_read(n_records_to_read)
{
  load_dlib_funcs();
}

TableReader::~TableReader() {
  unload_dlib_funcs();
}

SmartdbErr TableReader::run(const Scheduler & scheduler) {
  return read();
}

SmartdbErr TableReader::read() {
  uintptr_t ret;  // hack: functions loaded by dlsym() seem to return void *.
                  // void * => SmartdbErr is prohibited.

  ret = (uintptr_t)storage_funcs.storage_init(logger, extra);
  if (ret != (uintptr_t)NO_ERR) return (SmartdbErr)ret;

  std::vector<Buffer *> colbufs(coldefs.size(), NULL);
  std::vector<size_t> colbuf_sizes(coldefs.size(), 0);

  size_t read_records = 0;
  bool finished = false;
  while (!finished) {
    // prepare for Records
    for (size_t i = 0; i < colbuf_sizes.size(); ++i) {
      // [TODO] - calculate average size of variable-sized column
      colbuf_sizes[i] = coldefs[i]->size() * n_records_to_read;
    }
    Records *records = new Records(coldefs, colbuf_sizes);

    ret = (uintptr_t)storage_funcs.storage_read_records(
      *records, n_records_to_read, read_records, finished);
    if (ret != (uintptr_t)NO_ERR) goto fin;
    ASSERT(read_records > 0);
    out_q.push(records);
  }

  out_q.finish();
  ret = (uintptr_t)NO_ERR;
fin:
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
