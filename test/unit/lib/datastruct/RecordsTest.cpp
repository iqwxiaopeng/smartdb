#include "gtest/gtest.h"
#include <vector>
#include "datastruct/Records.h"
#include "api/SmartdbType.h"
#include "hack/Assert.h"

using namespace Smartdb;

class RecordsTest : public ::testing::Test {
protected:
  SmartdbValue v;

  virtual void SetUp() {
  }
};

TEST_F(RecordsTest, add_and_get_to_single_column) {
  ColumnDef coldef("col1", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(1, &coldef);

  std::vector<size_t> buf_sizes(1, 1024);

  Records *records = new Records(coldefs, buf_sizes);

  SET_SMARTDB_VALUE(v, SmartdbInt, 777); records->columns[0]->add(v);
  EXPECT_EQ(777, GET_SMARTDB_VALUE(records->columns[0]->get(0), SmartdbInt));
}
TEST_F(RecordsTest, add_and_get_to_multiple_column) {
  std::vector<size_t> buf_sizes(2, 1024);

  const ColumnDef coldef1("col1", SMARTDB_INT);
  const ColumnDef coldef2("col2", SMARTDB_DOUBLE);
  std::vector<const ColumnDef *> coldefs(2, NULL);
  coldefs[0] = &coldef1;
  coldefs[1] = &coldef2;

  Records *records = new Records(coldefs, buf_sizes);

  SET_SMARTDB_VALUE(v, SmartdbInt, 777); records->columns[0]->add(v);
  SET_SMARTDB_VALUE(v, SmartdbDouble, 3.14); records->columns[1]->add(v);
  EXPECT_EQ(777, GET_SMARTDB_VALUE(records->columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(3.14, GET_SMARTDB_VALUE(records->columns[1]->get(0), SmartdbDouble));
}
