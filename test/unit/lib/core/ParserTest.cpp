/*
 * ParserTest.cpp
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#include "gtest/gtest.h"
#include "core/Parser.h"

using namespace Smartdb;

class ParserTest : public ::testing::Test {
protected:
  virtual void SetUp() {
  }
};

TEST_F(ParserTest, success_select_001) {
  ASSERT_NO_THROW(Parser("SELECT * FROM T;"));
}
