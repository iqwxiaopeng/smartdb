/*
 * SmartdbType.h
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_API_SMARTDBTYPE_H_
#define INCLUDE_API_SMARTDBTYPE_H_

#include <string>
#include <unordered_map>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include "hack/Assert.hpp"

namespace Smartdb {
  class Schema;
}

typedef struct smartdb {
  Smartdb::Schema * schema;
} smartdb;

typedef struct smartdb_stmt {
  // [TODO] - everything
} smartdb_stmt;

//
// embedded types of Smartdb
enum SmartdbType {
  SMARTDB_INT = 1,
  SMARTDB_DOUBLE,
};

typedef int32_t SmartdbInt;
typedef double SmartdbDouble;

typedef union SmartdbValue {
  SmartdbDouble v_SmartdbDouble;
  SmartdbInt v_SmartdbInt;
} SmartdbValue;

#define GET_SMARTDB_VALUE(var, type) var.v_##type
#define SET_SMARTDB_VALUE(var, type, val) (var.v_##type = val);

inline
SmartdbValue str_to_SmartdbValue(const std::string &str, SmartdbType type) {
  SmartdbValue val;

  switch (type) {
  case SMARTDB_INT:
    val.v_SmartdbInt = std::atoi(str.c_str());
    break;
  case SMARTDB_DOUBLE:
    val.v_SmartdbDouble = std::atof(str.c_str());
    break;
  default:
    ASSERT(false);
  }

  return val;
}

//
// error types
enum SmartdbErr {
  NO_ERR = 0,
  PHYSICAL_MEM_SHORTAGE,  // Cannot allocate memory
  MEM_BUF_SHORTAGE,       // `Buffer` space is not enough
  IO_ERR,
  UNKNOWN_COLUMN,
  NO_MORE_RECORD,

  ERR,
};

//
// dynamic library treatment
#ifdef _WIN32
#include <windows.h>
typedef HANDLE lib_t;
#else
#include <dlfcn.h>
typedef void* lib_t;
#endif

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

#endif /* INCLUDE_API_SMARTDBTYPE_H_ */
