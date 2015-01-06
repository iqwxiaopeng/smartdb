#include <cstdlib>
#include <cstdint>
#include "op/TableReader.hpp"
#include "storageinterface/Records.hpp"
#include "hack/DynamicLib.hpp"
#include "log/Logger.hpp"

namespace Smartdb {

extern Logger *logger;

//
// Static functions
storage_engine_lib_t * TableReader::init_storage_engine(
  const std::string & storage_engine_name,
  const std::unordered_map<std::string, std::string> & extra)
{
  storage_engine_lib_t * p = new storage_engine_lib_t;
  load_dlib_funcs(storage_engine_name, &(p->dlib_handler), &(p->storage_funcs));
  p->storage_status = p->storage_funcs.storage_init(logger, extra);
  ASSERT(p->storage_status);
  return p;
}

void TableReader::finish_storage_engine(storage_engine_lib_t * p) {
  p->storage_funcs.storage_finish(p->storage_status);
  unload_dlib_funcs(p->dlib_handler);
}

inline std::string TableReader::dlib_name_without_suffix(const std::string & storage_engine_name) {
  return std::string("libsmartdb_engine_") + storage_engine_name;
}

#define FIND_DLIB(logger, dlib_handler, dlib_name, dlib_suffix) \
{ \
  if (!(dlib_handler = load_dlib((dlib_name + dlib_suffix).c_str()))) \
    logger->info(::dlerror()); \
  else \
    logger->info((std::string("Found ") + dlib_name + dlib_suffix).c_str()); \
}

#define LOAD_FUNC(logger, dlib_handler, storage_funcs, func_name) \
  if (!((storage_funcs).func_name = \
        (func_name ## _t)load_func(dlib_handler, #func_name))) { \
    logger->error(::dlerror()); \
    std::abort(); \
  }

inline void TableReader::load_dlib_funcs(
  const std::string & storage_engine_name,
  /*out*/
  lib_t * dlib_handler,
  storage_funcs_t * storage_funcs)
{
  std::string name = dlib_name_without_suffix(storage_engine_name);

  lib_t _dlib_handler = *dlib_handler;
  _dlib_handler = 0;
  if (!_dlib_handler) FIND_DLIB(logger, _dlib_handler, name, ".so");
  if (!_dlib_handler) FIND_DLIB(logger, _dlib_handler, name, ".dylib");

  if (!_dlib_handler) {
    logger->error((std::string("Could not load ") + name + ". Check if it is in correct library path. e.g. /usr/lib/").c_str());
    print_stacktrace();
    std::abort();
  }

  LOAD_FUNC(logger, _dlib_handler, *storage_funcs, storage_init);
  LOAD_FUNC(logger, _dlib_handler, *storage_funcs, storage_read_records);
  LOAD_FUNC(logger, _dlib_handler, *storage_funcs, storage_finish);
}

inline void TableReader::unload_dlib_funcs(lib_t dlib_handler) {
  ASSERT(dlib_handler);
  unload_dlib(dlib_handler);
}


// Member functions
TableReader::TableReader(const OperatorParam * const param)
: param((TableReaderParam*)param)
{}

TableReader::~TableReader() {}

SmartdbErr TableReader::run(const Scheduler & scheduler) {
  return read();
}

SmartdbErr TableReader::read() {
  uintptr_t ret;  // hack: functions loaded by dlsym() seem to return void *.
                  // void * => SmartdbErr is prohibited.

  std::vector<Buffer *> colbufs(param->coldefs.size(), NULL);
  std::vector<size_t> n_rows(param->coldefs.size(), param->records_chunk_size);

  size_t n_read_records = 0;
  bool finished = false;
  while (!finished) {
    // prepare for Records
    Records *records = new Records(param->coldefs, n_rows);  // [FIXME] - delete

    ret = (uintptr_t)param->engine->storage_funcs.storage_read_records(
      param->engine->storage_status, param->records_chunk_size, *records, n_read_records, finished);
    if (ret != (uintptr_t)NO_ERR) goto fin;
    ASSERT(finished || n_read_records > 0);
    if (n_read_records > 0) out_q.push(records);
  }

  out_q.finish();
  ret = (uintptr_t)NO_ERR;

fin:
  return (SmartdbErr)ret;
}

}
