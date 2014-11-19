#include "gtest/gtest.h"
#include "datastruct/FixedLengthColumn.h"
#include "api/SmartdbType.h"
#include "datastruct/ColumnDef.h"
#include "hack/Assert.h"

using namespace Smartdb;

class FixedLengthColumnTest : public ::testing::Test {
protected:
  Buffer buf;
  SmartdbValue v;
  ColumnDef coldef_int, coldef_double;

  FixedLengthColumnTest()
  : buf(1024),
    coldef_int("col1", SMARTDB_INT), coldef_double("col1", SMARTDB_DOUBLE)
  {}

  virtual void SetUp() {
  }
};

TEST_F(FixedLengthColumnTest, add_returns_no_error) {
  FixedLengthColumn col(coldef_int, buf);
  SET_SMARTDB_VALUE(v, SmartdbInt, 777);
  EXPECT_EQ(NO_ERR, col.add(v));
}
TEST_F(FixedLengthColumnTest, add_returns_no_error_on_multiple_addition) {
  FixedLengthColumn col(coldef_int, buf);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123);
  EXPECT_EQ(NO_ERR, col.add(v));
  SET_SMARTDB_VALUE(v, SmartdbInt, 456);
  EXPECT_EQ(NO_ERR, col.add(v));
}
TEST_F(FixedLengthColumnTest, add_returns_MEM_BUF_SHORTAGE_on_too_much_addition) {
  Buffer buf(1);
  FixedLengthColumn col(coldef_int, buf);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123);
  EXPECT_EQ(MEM_BUF_SHORTAGE, col.add(v));
}

TEST_F(FixedLengthColumnTest, get_returns_added_value) {
  FixedLengthColumn col(coldef_int, buf);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123); col.add(v);
  EXPECT_EQ(123, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));
}
TEST_F(FixedLengthColumnTest, get_returns_double_value) {
  FixedLengthColumn col(coldef_double, buf);
  SET_SMARTDB_VALUE(v, SmartdbDouble, 3.14); col.add(v);
  EXPECT_EQ(3.14, GET_SMARTDB_VALUE(col.get(0), SmartdbDouble));
}
TEST_F(FixedLengthColumnTest, get_returns_2nd_added_value) {
  FixedLengthColumn col(coldef_int, buf);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123); col.add(v);
  SET_SMARTDB_VALUE(v, SmartdbInt, 456); col.add(v);
  EXPECT_EQ(123, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));
  EXPECT_EQ(456, GET_SMARTDB_VALUE(col.get(1), SmartdbInt));
}
TEST_F(FixedLengthColumnTest, get_reentrant) {
  FixedLengthColumn col(coldef_int, buf);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123); col.add(v);
  SET_SMARTDB_VALUE(v, SmartdbInt, 456); col.add(v);
  EXPECT_EQ(123, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));
  EXPECT_EQ(456, GET_SMARTDB_VALUE(col.get(1), SmartdbInt));
  EXPECT_EQ(123, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));
  EXPECT_EQ(456, GET_SMARTDB_VALUE(col.get(1), SmartdbInt));
}
TEST_F(FixedLengthColumnTest, get_assertion_fails_on_invalid_column_range) {
  FixedLengthColumn col(coldef_int, buf);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123); col.add(v);
  ASSERT_THROW(col.get(1), SmartdbAssertionFailed);
}

TEST_F(FixedLengthColumnTest, clear) {
  FixedLengthColumn col(coldef_int, buf);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123); col.add(v);
  EXPECT_EQ(123, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));

  col.clear();
  SET_SMARTDB_VALUE(v, SmartdbInt, 456); col.add(v);
  EXPECT_EQ(456, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));
}
