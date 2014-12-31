#include "gtest/gtest.h"
#include "datastruct/RecordsQueue.hpp"
#include "api/SmartdbType.hpp"
#include "hack/Assert.hpp"

using namespace Smartdb;

class RecordsQueueTest : public ::testing::Test {
protected:
  RecordsQueue q;
  virtual void SetUp() {
  }
};

TEST_F(RecordsQueueTest, push_front_pop) {
  const ColumnDef coldef1("col1", SMARTDB_INT);
  const ColumnDef coldef2("col2", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(2, NULL);
  coldefs[0] = &coldef1;
  coldefs[1] = &coldef2;

  std::vector<size_t> buf_sizes(2, 1024);

  Records *records = new Records(coldefs, buf_sizes);

  EXPECT_EQ(NULL, q.front());
  q.push(records);
  EXPECT_EQ(records, q.front());
  q.pop();
  EXPECT_EQ(NULL, q.front());
}
TEST_F(RecordsQueueTest, FIFO) {
  std::vector<size_t> buf_sizes(1, 1024);

  const ColumnDef coldef1("col1", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs1(1, &coldef1);
  Records *records1 = new Records(coldefs1, buf_sizes);

  const ColumnDef coldef2("col1", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs2(1, &coldef2);
  Records *records2 = new Records(coldefs2, buf_sizes);

  q.push(records1);
  q.push(records2);
  EXPECT_EQ(records1, q.front());
  q.pop();
  EXPECT_EQ(records2, q.front());
  q.pop();
  EXPECT_EQ(NULL, q.front());
}
