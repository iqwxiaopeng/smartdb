#include "gtest/gtest.h"
#include "datastruct/Record.h"

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
TEST(get_int, reentrant) {
  Record rec(2, buf);
  rec.add_int(123);
  rec.add_int(456);
  EXPECT_EQ(123, rec.get_int(0));
  EXPECT_EQ(456, rec.get_int(1));
  EXPECT_EQ(123, rec.get_int(0));
  EXPECT_EQ(456, rec.get_int(1));
}
TEST(get_int, returns_MEM_BUF_SHORTAGE_when_adding_too_much_columns) {
  const size_t bufsz = 7;
  Buffer buf(bufsz);

  Record rec(bufsz, buf);
  EXPECT_EQ(NO_ERR, rec.add_int(123));
  EXPECT_EQ(MEM_BUF_SHORTAGE, rec.add_int(123));
}
