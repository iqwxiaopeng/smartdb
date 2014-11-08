#include "gtest/gtest.h"
#include "datastruct/Record.h"
#include "datastruct/Buffer.h"

using namespace Smartdb;

const size_t bufsz = 1024;
Buffer buf(bufsz);

TEST(add_int, returns_no_error) {
  Record rec(1, buf);
  EXPECT_EQ(NO_ERR, rec.add_int(123));
}
TEST(add_int, returns_no_error_on_multiple_addition) {
  Record rec(2, buf);
  EXPECT_EQ(NO_ERR, rec.add_int(123));
  EXPECT_EQ(NO_ERR, rec.add_int(456));
}

TEST(get_int, returns_added_value) {
  Record rec(1, buf);
  rec.add_int(123);
  EXPECT_EQ(123, rec.get_int(0));
}
TEST(get_int, returns_2nd_added_value) {
  Record rec(2, buf);
  rec.add_int(123);
  rec.add_int(456);
  EXPECT_EQ(123, rec.get_int(0));
  EXPECT_EQ(456, rec.get_int(1));
}
