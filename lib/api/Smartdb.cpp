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

} /* namespace Smartdb */

extern "C"
void smartdb_init() {
#if Logger == Stderr
  Smartdb::logger = new Smartdb::StderrLogger();
#else
  Smartdb::logger = new Smartdb::StderrLogger();
#endif
}

extern "C"
void smartdb_finish() {
  if (Smartdb::logger) delete Smartdb::logger;
}
