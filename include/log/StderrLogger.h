/*
 * StderrLogger.h
 *
 *  Created on: 2014/11/18
 *      Author: nakatani.sho
 */

#ifndef LIB_LOG_STDERRLOGGER_H_
#define LIB_LOG_STDERRLOGGER_H_

#include "Logger.h"
#include "hack/Class.h"

namespace Smartdb {

class StderrLogger : public Logger {
public:
  StderrLogger();
  virtual ~StderrLogger();

  void error(const char * const msg);
  void warn(const char * const msg);
  void info(const char * const msg);
  void debug(const char * const msg);

  PREVENT_COPY_CONSTRUCTOR(StderrLogger);
  PREVENT_OBJECT_ASSIGNMENT(StderrLogger);
};

} /* namespace Smartdb */

#endif /* LIB_LOG_STDERRLOGGER_H_ */
