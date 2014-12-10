/*
 * Assert.h
 *
 *  Created on: 2014/11/09
 *      Author: nakatani.sho
 */

#ifndef LIB_HACK_ASSERT_H_
#define LIB_HACK_ASSERT_H_

#ifdef SMARTDB_GTEST
#include <stdexcept>
#include <string>

class SmartdbAssertionFailed : public std::runtime_error {
public:
  SmartdbAssertionFailed(const std::string &cause)
  : std::runtime_error(cause)
  {}
};

#define ASSERT(cond) \
  if (!(cond)) \
    throw SmartdbAssertionFailed( \
      std::string(__FILE__) + ":" + std::to_string(__LINE__) + " SmartdbAssertionFailed: " + #cond);

#else /* SMARTDB_GTEST */
#include <assert.h>

#define ASSERT(cond) \
  assert(cond);

#endif /* SMARTDB_GTEST */

#endif /* LIB_HACK_ASSERT_H_ */
