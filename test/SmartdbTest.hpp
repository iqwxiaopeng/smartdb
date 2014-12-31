/*
 * SmartdbTest.h
 *
 *  Created on: 2014/11/20
 *      Author: nakatani.sho
 */

#ifndef TEST_UNIT_SMARTDBTEST_H_
#define TEST_UNIT_SMARTDBTEST_H_

#include "gtest/gtest.h"
#include "api/Smartdb.hpp"

namespace Smartdb {

class SmartdbTest : public ::testing::Test {
public:
  SmartdbTest() { smartdb_init(); }
  virtual ~SmartdbTest() { smartdb_finish(); }
};

} /* namespace Smartdb */

#endif /* TEST_UNIT_SMARTDBTEST_H_ */
