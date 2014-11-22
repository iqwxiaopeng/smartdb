/*
 * StderrLogger.cpp
 *
 *  Created on: 2014/11/18
 *      Author: nakatani.sho
 */

#include <iostream>
#include "log/StderrLogger.h"

namespace Smartdb {


StderrLogger::StderrLogger() {
}

StderrLogger::~StderrLogger() {
  // TODO Auto-generated destructor stub
}

void StderrLogger::error(const char* const msg) {
  std::cerr << "[Error] " << msg << std::endl;
}

void StderrLogger::warn(const char* const msg) {
  std::cerr << "[Warn] " << msg << std::endl;
}

void StderrLogger::info(const char* const msg) {
  std::cerr << "[Info] " << msg << std::endl;
}
void StderrLogger::debug(const char* const msg) {
  std::cerr << "[Debug] " << msg << std::endl;
}

} /* namespace Smartdb */
