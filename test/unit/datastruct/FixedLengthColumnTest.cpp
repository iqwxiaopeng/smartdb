#include "gtest/gtest.h"
#include "datastruct/FixedLengthColumn.h"
#include "hack/Assert.h"

using namespace Smartdb;

class FixedLengthColumnTest : public ::testing::Test {
protected:
  static const size_t bufsz = 1024;
  Buffer buf;

  virtual void SetUp() {
    buf.allocate(bufsz);
  }
};

TEST_F(FixedLengthColumnTest, add_returns_no_error) {
  FixedLengthColumn<SmartdbInt> col(buf);
  EXPECT_EQ(NO_ERR, col.add(123));
}
TEST_F(FixedLengthColumnTest, add_returns_no_error_on_multiple_addition) {
  FixedLengthColumn<SmartdbInt> col(buf);
  EXPECT_EQ(NO_ERR, col.add(123));
  EXPECT_EQ(NO_ERR, col.add(456));
}
TEST_F(FixedLengthColumnTest, add_returns_MEM_BUF_SHORTAGE_on_too_much_addition) {
  Buffer buf;
  buf.allocate(1);
  FixedLengthColumn<SmartdbInt> col(buf);
  EXPECT_EQ(MEM_BUF_SHORTAGE, col.add(123));
}

TEST_F(FixedLengthColumnTest, get_returns_added_value) {
  FixedLengthColumn<SmartdbInt> col(buf);
  col.add(123);
  EXPECT_EQ(123, col.get(0));
}
TEST_F(FixedLengthColumnTest, get_returns_2nd_added_value) {
  FixedLengthColumn<SmartdbInt> col(buf);
  col.add(123);
  col.add(456);
  EXPECT_EQ(123, col.get(0));
  EXPECT_EQ(456, col.get(1));
}
TEST_F(FixedLengthColumnTest, get_reentrant) {
  FixedLengthColumn<SmartdbInt> col(buf);
  col.add(123);
  col.add(456);
  EXPECT_EQ(123, col.get(0));
  EXPECT_EQ(456, col.get(1));
  EXPECT_EQ(123, col.get(0));
  EXPECT_EQ(456, col.get(1));
}
TEST_F(FixedLengthColumnTest, get_assertion_fails_on_invalid_column_range) {
  FixedLengthColumn<SmartdbInt> col(buf);
  col.add(123);
  ASSERT_THROW(col.get(1), SmartdbAssertionFailed);
}
