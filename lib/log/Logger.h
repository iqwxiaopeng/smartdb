/*
 * Logger.h
 *
 *  Created on: 2014/11/18
 *      Author: nakatani.sho
 */

#ifndef LIB_LOG_LOGGER_H_
#define LIB_LOG_LOGGER_H_

namespace Smartdb {

class Logger {
public:
  virtual ~Logger() {}

  virtual void error(const char * const msg) = 0;
  virtual void warn(const char * const msg) = 0;
  virtual void info(const char * const msg) = 0;
  virtual void debug(const char * const msg) = 0;
};

extern Logger *logger;

} /* namespace Smartdb */

#endif /* LIB_LOG_LOGGER_H_ */
