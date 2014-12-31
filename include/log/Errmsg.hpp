/*
 * Errmsg.h
 *
 *  Created on: 2014/11/22
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_LOG_ERRMSG_H_
#define INCLUDE_LOG_ERRMSG_H_

#include "hack/Assert.hpp"

extern "C"
const char * smartdb_errmsg(SmartdbErr err) {
  switch (err) {
  case NO_ERR: return "Success.";
  case PHYSICAL_MEM_SHORTAGE: return "Cannot allocate memory from kernel.";
  case MEM_BUF_SHORTAGE: return "`Buffer` does not have enough memory.";
  case IO_ERR: return "IO error.";
  case UNKNOWN_COLUMN: return "Unknown column is specified.";
  case ERR: return "Something wrong happened.";
  default: ASSERT(false); return "";
  }
}


#endif /* INCLUDE_LOG_ERRMSG_H_ */
