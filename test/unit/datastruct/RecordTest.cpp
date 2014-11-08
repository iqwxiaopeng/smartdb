#include "gtest/gtest.h"
#include "datastruct/Record.h"

TEST(hello, first) {
  EXPECT_EQ(Smartdb::hello(), 777);
}
TEST(hello, second) {
  EXPECT_EQ(Smartdb::hello(), 888);
}
