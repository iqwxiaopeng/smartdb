#include "gtest/gtest.h"
#include <vector>
#include "datastruct/Records.h"
#include "api/SmartdbType.h"
#include "mem/Buffer.h"
#include "hack/Assert.h"

using namespace Smartdb;

class RecordsTest : public ::testing::Test {
protected:
  SmartdbValue v;

  virtual void SetUp() {
  }
};

TEST_F(RecordsTest, add_and_get_to_single_column) {
  Buffer colbuf(1024);
  ColumnDef coldef("col1", SMARTDB_INT);

  Records records(
    std::vector<const ColumnDef * const>(1, &coldef),
    std::vector<Buffer * const>(1, &colbuf));

  SET_SMARTDB_VALUE(v, SmartdbInt, 777); records.columns[0]->add(v);
  EXPECT_EQ(777, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
}
TEST_F(RecordsTest, add_and_get_to_multiple_column) {
  const ColumnDef coldef1("col1", SMARTDB_INT);
  const ColumnDef coldef2("col2", SMARTDB_DOUBLE);
  std::vector<const ColumnDef *> coldefs(2, 0);
  coldefs.push_back(&coldef1);
  coldefs.push_back(&coldef2);

  Buffer colbuf1(1024);
  Buffer colbuf2(1024);
  std::vector<Buffer *> colbufs(2, 0);
  colbufs.push_back(&colbuf1);
  colbufs.push_back(&colbuf2);

  Records records(coldefs, colbufs);

  SET_SMARTDB_VALUE(v, SmartdbInt, 777); records.columns[0]->add(v);
  SET_SMARTDB_VALUE(v, SmartdbDouble, 3.14); records.columns[1]->add(v);
  EXPECT_EQ(777, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(3.14, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbDouble));
}
