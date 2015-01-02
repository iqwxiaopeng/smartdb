#include <cstdlib>
#include <cstdint>
#include "op/TableReader.hpp"
#include "storageinterface/Records.hpp"
#include "hack/DynamicLib.hpp"
#include "log/Logger.hpp"

#define LOAD_FUNC(func_name) \
  if (!(storage_funcs.func_name = \
        (func_name ## _t)load_func(dlib_handler, #func_name))) { \
    logger->error(::dlerror()); \
    std::abort(); \
  }


namespace Smartdb {

extern
Logger *logger;

TableReader::TableReader(const OperatorParam * const param)
: param((TableReaderParam*)param), dlib_handler(0)
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

  // [TODO] - storage_init() should not be called from each instance of TableReader.
  ret = (uintptr_t)storage_funcs.storage_init(logger, param->extra);
  if (ret != (uintptr_t)NO_ERR) return (SmartdbErr)ret;

  std::vector<Buffer *> colbufs(param->coldefs.size(), NULL);
  std::vector<size_t> colbuf_sizes(param->coldefs.size(), 0);

  size_t n_read_records = 0;
  bool finished = false;
  while (!finished) {
    // prepare for Records
    for (size_t i = 0; i < colbuf_sizes.size(); ++i) {
      // [TODO] - calculate average size of variable-sized column
      colbuf_sizes[i] = param->coldefs[i]->size() * param->records_chunk_size;
    }
    Records *records = new Records(param->coldefs, colbuf_sizes);  // [FIXME] - delete

    ret = (uintptr_t)storage_funcs.storage_read_records(
      param->records_chunk_size, *records, n_read_records, finished);
    if (ret != (uintptr_t)NO_ERR) goto fin;
    ASSERT(finished || n_read_records > 0);
    if (n_read_records > 0) out_q.push(records);
  }

  out_q.finish();
  ret = (uintptr_t)NO_ERR;

fin:
  storage_funcs.storage_finish();
  return (SmartdbErr)ret;
}

inline
std::string TableReader::dlib_name_without_suffix() {
  return std::string("lib") + param->storage_engine_name;
}

inline
void TableReader::load_dlib_funcs() {
  if (!(dlib_handler = load_dlib((dlib_name_without_suffix() + ".so").c_str())))
    logger->info(::dlerror());
  if (!dlib_handler && !(dlib_handler = load_dlib((dlib_name_without_suffix() + ".dylib").c_str())))
    logger->info(::dlerror());
  if (!dlib_handler) {
    logger->error((std::string("Could not load ") + dlib_name_without_suffix() + ". Check if it is in correct library path. e.g. /usr/lib/").c_str());
    std::abort();
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
