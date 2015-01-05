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


/**
 * Signed 32-bit integer
 */
typedef int32_t SmartdbInt;

/**
 * Double-precision floating-point.
 */
typedef double SmartdbDouble;

/**
 * Return if given type enum represents fixed length type or not.
 */
#define IS_FIXED_LENGTH_TYPE(t) _FIXED_LENGTH_TYPE_BEGIN < (t) && (t) < _FIXED_LENGTH_TYPE_END

/**
 * Return the size of type enum.
 */
#define SMARTDB_SIZEOF(t) (size_t)((t) & 0xf)


/**
 * Embedded types of Smartdb.
 *
 * Each value should follow the following rules.
 * \li Least 4 bits represent the size of the type.
 * \li Fixed length type (int, char, double, ...) should have the value between 0x1000 and 0x1fff.
 * \li Variable length type (varchar, text, blob, ...) should have the value between 0x2000 and 0x2fff.
 */
enum SmartdbType {
  _FIXED_LENGTH_TYPE_BEGIN = 0x1000,//!< _FIXED_LENGTH_TYPE_BEGIN
  SMARTDB_INT = 0x1000 + 0x4,       //!< SMARTDB_INT
  SMARTDB_DOUBLE = 0x1010 + 0x8,    //!< SMARTDB_DOUBLE
  _FIXED_LENGTH_TYPE_END = 0x1fff,  //!< _FIXED_LENGTH_TYPE_END

  _VAR_LENGTH_TYPE_BEGIN = 0x2000,           //!< _VAR_LENGTH_TYPE_BEGIN
  _VAR_LENGTH_TYPE_END = 0x2fff,             //!< _VAR_LENGTH_TYPE_END
};


typedef union SmartdbValue {
  SmartdbDouble v_SmartdbDouble;
  SmartdbInt v_SmartdbInt;
} SmartdbValue;

#define GET_SMARTDB_VALUE(var, type) var.v_##type
#define SET_SMARTDB_VALUE(var, type, val) (var.v_##type = val);

inline SmartdbValue str_to_SmartdbValue(const std::string &str, SmartdbType type) {
  SmartdbValue val;

  switch (type) {
  case SMARTDB_INT:
    val.v_SmartdbInt = std::atoi(str.c_str());
    break;
  case SMARTDB_DOUBLE:
    val.v_SmartdbDouble = std::atof(str.c_str());
    break;
  default:
    NOT_IMPLEMENTED;
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
