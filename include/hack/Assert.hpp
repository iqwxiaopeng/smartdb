/*
 * Assert.h
 *
 *  Created on: 2014/11/09
 *      Author: nakatani.sho
 */

#ifndef LIB_HACK_ASSERT_H_
#define LIB_HACK_ASSERT_H_

#include "hack/stacktrace.h"

#ifdef SMARTDB_GTEST
#include <stdexcept>
#include <sstream>
#include <string>

class SmartdbAssertionFailed : public std::runtime_error {
public:
  SmartdbAssertionFailed(const std::string &cause)
  : std::runtime_error(cause)
  {}
};

#define ASSERT(cond) \
  if (!(cond)) { \
    print_stacktrace(); \
    std::ostringstream ss; \
    ss << __FILE__ << ":" << __LINE__ << " (in " << __FUNCTION__ << "())" << " SmartdbAssertionFailed: " << #cond; \
    throw SmartdbAssertionFailed(ss.str()); \
  }

#else /* SMARTDB_GTEST */
#include <cassert>

#define ASSERT(cond) \
  { \
    if (!(cond)) print_stacktrace(); \
    assert(cond); \
  }

#endif /* SMARTDB_GTEST */

#endif /* LIB_HACK_ASSERT_H_ */
