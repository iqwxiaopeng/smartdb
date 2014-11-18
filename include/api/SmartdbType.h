/*
 * SmartdbType.h
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_API_SMARTDBTYPE_H_
#define INCLUDE_API_SMARTDBTYPE_H_

#include <stddef.h>
#include <stdint.h>

//
// embedded types of Smartdb
enum SmartdbType {
  SMARTDB_INT = 0,
};
typedef int32_t SmartdbInt;

//
// error types
enum SmartdbErr {
  NO_ERR = 0,
  PHYSICAL_MEM_SHORTAGE,  // Cannot allocate memory
  MEM_BUF_SHORTAGE,       // `Buffer` space is not enough
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

typedef SmartdbErr (storage_init_t)(Smartdb::Logger * const logger);
typedef SmartdbErr (storage_read_records_t)(Smartdb::Records &, size_t);
typedef struct storage_funcs_t {
  storage_init_t storage_init;
  storage_read_records_t storage_read_records;
} storage_funcs_t;

#endif /* INCLUDE_API_SMARTDBTYPE_H_ */
