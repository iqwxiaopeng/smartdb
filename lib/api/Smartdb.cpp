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

Logger *logger;

void smartdb_init() {
#if Logger == Stderr
  logger = new StderrLogger();
#else
  logger = new StderrLogger();
#endif
}

} /* namespace Smartdb */
