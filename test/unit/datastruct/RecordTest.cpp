#include "gtest/gtest.h"
#include "datastruct/Record.h"
#include "hack/Assert.h"

using namespace Smartdb;

class RecordTest : public ::testing::Test {
protected:
  static const size_t bufsz = 1024;
  Buffer buf;

  virtual void SetUp() {
    buf.allocate(bufsz);
  }
};

TEST_F(RecordTest, add_int_returns_no_error) {
  Record rec(1, buf);
  EXPECT_EQ(NO_ERR, rec.add_int(123));
}
TEST_F(RecordTest, add_int_returns_no_error_on_multiple_addition) {
  Record rec(2, buf);
  EXPECT_EQ(NO_ERR, rec.add_int(123));
  EXPECT_EQ(NO_ERR, rec.add_int(456));
}
TEST_F(RecordTest, add_int_assertion_fails_on_too_much_addition) {
  Record rec(1, buf);
  EXPECT_EQ(NO_ERR, rec.add_int(123));
  EXPECT_EQ(NO_ERR, rec.add_int(123));
  ASSERT_THROW(rec.add_int(456), SmartdbAssertionFailed);
}

TEST_F(RecordTest, get_int_returns_added_value) {
  Record rec(1, buf);
  rec.add_int(123);
  EXPECT_EQ(123, rec.get_int(0));
}
TEST_F(RecordTest, get_int_returns_2nd_added_value) {
  Record rec(2, buf);
  rec.add_int(123);
  rec.add_int(456);
  EXPECT_EQ(123, rec.get_int(0));
  EXPECT_EQ(456, rec.get_int(1));
}
TEST_F(RecordTest, get_int_reentrant) {
  Record rec(2, buf);
  rec.add_int(123);
  rec.add_int(456);
  EXPECT_EQ(123, rec.get_int(0));
  EXPECT_EQ(456, rec.get_int(1));
  EXPECT_EQ(123, rec.get_int(0));
  EXPECT_EQ(456, rec.get_int(1));
}
TEST_F(RecordTest, get_int_assertion_fails_on_invalid_column_range) {
  Record rec(1, buf);
  rec.add_int(123);
  ASSERT_THROW(rec.get_int(1), SmartdbAssertionFailed);
}
TEST_F(RecordTest, get_int_returns_MEM_BUF_SHORTAGE_when_adding_too_much_columns) {
  const size_t bufsz = 7;
  Buffer buf;
  buf.allocate(bufsz);

  Record rec(bufsz, buf);
  EXPECT_EQ(NO_ERR, rec.add_int(123));
  EXPECT_EQ(MEM_BUF_SHORTAGE, rec.add_int(123));
}
