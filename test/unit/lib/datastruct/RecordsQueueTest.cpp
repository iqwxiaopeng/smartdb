#include "gtest/gtest.h"
#include "datastruct/RecordsQueue.h"
#include "api/SmartdbType.h"
#include "hack/Assert.h"

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

  Buffer colbuf1(1024);
  Buffer colbuf2(1024);
  std::vector<Buffer *> colbufs(2, NULL);
  colbufs[0] = &colbuf1;
  colbufs[1] = &colbuf2;

  Records records(coldefs, colbufs);

  EXPECT_EQ(NULL, q.front());
  q.push(&records);
  EXPECT_EQ(&records, q.front());
  q.pop();
  EXPECT_EQ(NULL, q.front());
}
TEST_F(RecordsQueueTest, FIFO) {
  const ColumnDef coldef1("col1", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs1(1, &coldef1);
  Buffer colbuf1(1024);
  std::vector<Buffer *> colbufs1(1, &colbuf1);
  Records records1(coldefs1, colbufs1);

  const ColumnDef coldef2("col1", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs2(1, &coldef2);
  Buffer colbuf2(1024);
  std::vector<Buffer *> colbufs2(1, &colbuf2);
  Records records2(coldefs2, colbufs2);

  q.push(&records1);
  q.push(&records2);
  EXPECT_EQ(&records1, q.front());
  q.pop();
  EXPECT_EQ(&records2, q.front());
  q.pop();
  EXPECT_EQ(NULL, q.front());
}
