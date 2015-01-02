/*
 * Errmsg.cpp
 *
 *  Created on: 2015/01/03
 *      Author: nakatani.sho
 */

#include "log/Errmsg.hpp"
#include "hack/Assert.hpp"

const char * smartdb_errmsg(SmartdbErr err) {
  switch (err) {
  case NO_ERR: return "Success.";
  case PHYSICAL_MEM_SHORTAGE: return "Cannot allocate memory from kernel.";
  case IO_ERR: return "IO error.";
  case UNKNOWN_COLUMN: return "Unknown column is specified.";
  case ERR: return "Something wrong happened.";
  default: ASSERT(false); return "";
  }
}
