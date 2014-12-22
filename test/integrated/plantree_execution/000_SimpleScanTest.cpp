#include "gtest/gtest.h"
#include "SmartdbTest.h"
#include "op/TableReader.h"
#include "op/OperatorParam.h"
#include "core/Executor.h"
#include "core/Scheduler.h"

using namespace Smartdb;

class SimpleScanTest : public SmartdbTest {
protected:
  virtual void SetUp() {
  }

  const size_t num_workers = 4;
};

TEST_F(SimpleScanTest, scan_from_csv) {
  // Create executor
  Executor executor(num_workers);

  // Construct Plan Tree
  ColumnDef coldef("col1", SMARTDB_INT);
  TableReaderParam table_reader_param(
    std::vector<const ColumnDef *>(1, &coldef),
    "csv",
    { {"path", "fixture/storage_csv_normal.csv"} },
    100);
  //PlanNode(TABLE_READER, table_reader_param);

  // Create scheduler
  //Scheduler scheduler(並列度とかコア数とか??);  <- ワーカ作るとかになると、スケジューラというかはexecutor??
  //Schedulerは、Plan treeをinputし、run queueをoutputする。run queueの各要素は、自分は最大何コアで実行されるという情報も持つ。
  // run queueはPlan treeを見た瞬間決定できるものではなく、動的にpush/pop。
  // input Records と output Records の順序は保つので、同じopが複数run queueに入ることは認めない。
  // executorは、ワーカみたいな構造を持つ。
  // 実際に各opを何コアで実行するかの判断を委ねられている。

  //Scheduler scheduler(executor, op);  // root opを与える
  //scheduler.execute();
  // この間に、schedulerに進捗を聞けたりするようにしたい
  //scheduler.join();

  /*while (!op.out_q.finished()) {
    const Records *records = op.out_q.front();
    EXPECT_NE((Records *)NULL, records);
    EXPECT_EQ(3, records->size());

    EXPECT_EQ(101, GET_SMARTDB_VALUE(records->columns[0]->get(0), SmartdbInt));
    EXPECT_EQ(201, GET_SMARTDB_VALUE(records->columns[0]->get(1), SmartdbInt));
    EXPECT_EQ(301, GET_SMARTDB_VALUE(records->columns[0]->get(2), SmartdbInt));
    op.out_q.pop();
  }*/
}
TEST_F(SimpleScanTest, scan_filter) {
  // Filter op を root として作成
  // TableReader op を作成し、親としてFilter opを登録

  // schedulerを作成  // TODO - 当然マルチスレッドにしていきたい

  // schedulerがTableReader == leafをrunnableにしつつ、プライオリティキューに入れる。プライオリティは(最もシンプルには)depth順。

  // schedulerがプライオリティキューからTableReader opを取り出して、MAX_PARALLELISMで実行。
  // TableReader がRecordsを吐いたら、TableReader::run()の中でそれをschedulerに通知。
  // schedulerはFilterをRunnableにする

  // MAX_PARALLELISMが低ければ、FilterとTableReader opは並列実行される。

  // TableReaderがEOFを読んだら、TableReader::run()の中でschedulerにそれを通知する。
}
