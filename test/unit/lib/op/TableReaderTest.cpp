#include <vector>
#include <unordered_map>
#include "SmartdbTest.hpp"
#include "op/TableReader.hpp"

#include "../../../../include/plantree/PlanNodeId.hpp"
#include "op/OperatorParam.hpp"
#include "plantree/PlanNode.hpp"
#include "core/Executor.hpp"
#include "core/Scheduler.hpp"
#include "storageinterface/ColumnDef.hpp"
#include "datastruct/RecordsQueue.hpp"
#include "hack/Assert.hpp"

using namespace Smartdb;

class TableReaderTest : public SmartdbTest {
protected:
  Executor dummy_executor;
  PlanNode dummy_root_plan;
  BinaryTree<PlanNode> dummy_plantree;
  Scheduler dummy_scheduler;

  TableReaderTest()
  : dummy_executor(1), dummy_root_plan(NULL_OPERATOR, NULL), dummy_plantree(&dummy_root_plan), dummy_scheduler(dummy_executor, dummy_plantree)
  {}

  virtual void SetUp() {
  }
};

TEST_F(TableReaderTest, reads_from_csv) {
  ColumnDef coldef("col1", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(1, &coldef);
  std::unordered_map<std::string, std::string> extra = { {"pathhhh", "fixture/storage_csv_normal.csv"} };
  std::string engine("csv");

  TableReaderParam param(coldefs, engine, extra, 100);
  TableReader op(&param);
  EXPECT_EQ(NO_ERR, op.run(dummy_scheduler));
  while (!op.out_q.finished()) {
    const Records *records = op.out_q.front();
    EXPECT_NE((Records *)NULL, records);
    EXPECT_EQ(3, records->size());

    EXPECT_EQ(101, GET_SMARTDB_VALUE(records->columns[0]->get(0), SmartdbInt));
    EXPECT_EQ(201, GET_SMARTDB_VALUE(records->columns[0]->get(1), SmartdbInt));
    EXPECT_EQ(301, GET_SMARTDB_VALUE(records->columns[0]->get(2), SmartdbInt));
    op.out_q.pop();
  }
}
TEST_F(TableReaderTest, reads_from_csv_record_by_record) {
  ColumnDef coldef("col1", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(1, &coldef);
  std::unordered_map<std::string, std::string> extra = { {"path", "fixture/storage_csv_normal.csv"} };
  std::string engine("csv");

  TableReaderParam param(coldefs, engine, extra, 1);
  TableReader op(&param);
  EXPECT_EQ(NO_ERR, op.run(dummy_scheduler));

  size_t records_cnt = 0;
  while (!op.out_q.finished()) {
    const Records *records = op.out_q.front(); ++records_cnt;
    EXPECT_NE((Records *)NULL, records);
    EXPECT_EQ(1, records->size());

    EXPECT_EQ(records_cnt * 100 + 1, GET_SMARTDB_VALUE(records->columns[0]->get(0), SmartdbInt));
    op.out_q.pop();
  }
}
