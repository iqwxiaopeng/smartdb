#include "gtest/gtest.h"
#include "storageinterface/FixedLengthColumn.hpp"
#include "api/SmartdbType.hpp"
#include "hack/Assert.hpp"

using namespace Smartdb;

class FixedLengthColumnTest : public ::testing::Test {
protected:
  SmartdbValue v;
  ColumnDef coldef_int, coldef_double;

  FixedLengthColumnTest()
  : coldef_int("col1", SMARTDB_INT), coldef_double("col1", SMARTDB_DOUBLE)
  {}

  virtual void SetUp() {
  }
};

TEST_F(FixedLengthColumnTest, add_returns_no_error) {
  FixedLengthColumn col(coldef_int);
  SET_SMARTDB_VALUE(v, SmartdbInt, 777);
  ASSERT_NO_THROW(col.add(v));
}
TEST_F(FixedLengthColumnTest, add_returns_no_error_on_multiple_addition) {
  FixedLengthColumn col(coldef_int);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123);
  ASSERT_NO_THROW(col.add(v));
  SET_SMARTDB_VALUE(v, SmartdbInt, 456);
  ASSERT_NO_THROW(col.add(v));
}
TEST_F(FixedLengthColumnTest, add_returns_successfully_even_when_min_n_rows_exceeds) {
  FixedLengthColumn col(coldef_int, 1);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123);
  ASSERT_NO_THROW(col.add(v));
  ASSERT_NO_THROW(col.add(v));
}

TEST_F(FixedLengthColumnTest, get_returns_added_value) {
  FixedLengthColumn col(coldef_int);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123); col.add(v);
  EXPECT_EQ(123, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));
}
TEST_F(FixedLengthColumnTest, get_returns_double_value) {
  FixedLengthColumn col(coldef_double);
  SET_SMARTDB_VALUE(v, SmartdbDouble, 3.14); col.add(v);
  EXPECT_EQ(3.14, GET_SMARTDB_VALUE(col.get(0), SmartdbDouble));
}
TEST_F(FixedLengthColumnTest, get_returns_2nd_added_value) {
  FixedLengthColumn col(coldef_int);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123); col.add(v);
  SET_SMARTDB_VALUE(v, SmartdbInt, 456); col.add(v);
  EXPECT_EQ(123, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));
  EXPECT_EQ(456, GET_SMARTDB_VALUE(col.get(1), SmartdbInt));
}
TEST_F(FixedLengthColumnTest, get_reentrant) {
  FixedLengthColumn col(coldef_int);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123); col.add(v);
  SET_SMARTDB_VALUE(v, SmartdbInt, 456); col.add(v);
  EXPECT_EQ(123, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));
  EXPECT_EQ(456, GET_SMARTDB_VALUE(col.get(1), SmartdbInt));
  EXPECT_EQ(123, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));
  EXPECT_EQ(456, GET_SMARTDB_VALUE(col.get(1), SmartdbInt));
}
TEST_F(FixedLengthColumnTest, get_assertion_fails_on_invalid_column_range) {
  FixedLengthColumn col(coldef_int);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123); col.add(v);
  ASSERT_THROW(col.get(1), SmartdbAssertionFailed);
}

TEST_F(FixedLengthColumnTest, clear) {
  FixedLengthColumn col(coldef_int);
  SET_SMARTDB_VALUE(v, SmartdbInt, 123); col.add(v);
  EXPECT_EQ(123, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));

  col.clear();
  SET_SMARTDB_VALUE(v, SmartdbInt, 456); col.add(v);
  EXPECT_EQ(456, GET_SMARTDB_VALUE(col.get(0), SmartdbInt));
}
