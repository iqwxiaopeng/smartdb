#ifndef SMARTDBSTORAGE_H
#define SMARTDBSTORAGE_H

#include "api/SmartdbType.hpp"
#include "log/Logger.hpp"
#include "log/Errmsg.hpp"
#include "storageinterface/Records.hpp"
#include "storageinterface/Buffer.hpp"
#include "storageinterface/ColumnDef.hpp"

//
// storage engine functions
namespace Smartdb {
  class Records;
  class Logger;
}

typedef void *(*storage_init_t)(Smartdb::Logger * const, const std::unordered_map<std::string, std::string> &);
// When storage_read_records() returns NO_ERR, read_records must be more than 0.
typedef void *(*storage_read_records_t)(size_t, Smartdb::Records&, size_t&, bool&);
typedef void *(*storage_finish_t)();

typedef struct storage_funcs_t {
  storage_init_t storage_init;
  storage_read_records_t storage_read_records;
  storage_finish_t storage_finish;
} storage_funcs_t;


#endif
