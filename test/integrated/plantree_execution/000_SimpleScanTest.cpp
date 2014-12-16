#include "gtest/gtest.h"
#include "op/TableReader.h"

using namespace Smartdb;

class SimpleScanTest : public ::testing::Test {
protected:
  virtual void SetUp() {
  }
};

TEST_F(SimpleScanTest, scan_from_csv) {
  // TableReader op を作成
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
