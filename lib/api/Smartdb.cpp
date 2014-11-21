/*
 * Smartdb.cpp
 *
 *  Created on: 2014/11/07
 *      Author: nakatani.sho
 */

#include "api/Smartdb.h"
#include "log/Logger.h"
#include "log/StderrLogger.h"

namespace Smartdb {

Logger *logger = 0;
std::unordered_map<int, const char *> _errmsg;

} /* namespace Smartdb */

extern "C"
void smartdb_init() {
  //
  // sets logger
#if Logger == Stderr
  Smartdb::logger = new Smartdb::StderrLogger();
#else
  Smartdb::logger = new Smartdb::StderrLogger();
#endif

  //
  //init error message dict
  Smartdb::_errmsg[NO_ERR] = "Success.";
  Smartdb::_errmsg[PHYSICAL_MEM_SHORTAGE] = "Cannot allocate memory from kernel.";
  Smartdb::_errmsg[MEM_BUF_SHORTAGE] = "`Buffer` does not have enough memory.";
  Smartdb::_errmsg[IO_ERR] = "IO error.";
  Smartdb::_errmsg[UNKNOWN_COLUMN] = "Unknown column is specified.";
  Smartdb::_errmsg[ERR] = "Something wrong happened.";
}

extern "C"
void smartdb_finish() {
  if (Smartdb::logger) delete Smartdb::logger;
}

extern "C"
const char * smartdb_errmsg(SmartdbErr err) {
  return Smartdb::_errmsg.at(err);
}
