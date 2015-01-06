#ifndef SMARTDBSTORAGE_H
#define SMARTDBSTORAGE_H

#include <vector>
#include "api/SmartdbType.hpp"
#include "log/Logger.hpp"
#include "storageinterface/Records.hpp"
#include "storageinterface/Buffer.hpp"

//
// storage engine functions
namespace Smartdb {
  class Records;
  class Logger;
}

typedef void *(*storage_init_t)(Smartdb::Logger * const, const std::unordered_map<std::string, std::string> &);
typedef SmartdbErr (*storage_read_records_t)(const void * const, size_t, Smartdb::Records&, size_t&, bool&);
typedef void (*storage_finish_t)(void *);

typedef struct storage_funcs_t {
  storage_init_t storage_init;
  storage_read_records_t storage_read_records;
  storage_finish_t storage_finish;
} storage_funcs_t;


#endif
