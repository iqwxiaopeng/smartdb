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

/**
 * Error types
 */
enum SmartdbErr {
  NO_ERR = 0,  //!<
  PHYSICAL_MEM_SHORTAGE,  //!< Cannot allocate memory
  IO_ERR,        //!< Error caused by disk I/O error
  UNKNOWN_COLUMN,//!< Accesses to column with unknown name
  NO_MORE_RECORD,//!<

  ERR,           //!< Other error
};


#endif /* INCLUDE_API_SMARTDBTYPE_H_ */
