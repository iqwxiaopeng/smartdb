#include <vector>
#include <unordered_map>
#include "SmartdbTest.h"
#include "op/TableReader.h"
#include "datastruct/ColumnDef.h"
#include "datastruct/RecordsQueue.h"
#include "hack/Assert.h"

using namespace Smartdb;

class TableReaderTest : public SmartdbTest {
protected:
  virtual void SetUp() {
  }
};

TEST_F(TableReaderTest, reads_from_csv) {
  ColumnDef coldef("col1", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(1, &coldef);

  std::unordered_map<std::string, std::string> extra = { {"path", "fixture/storage_csv_normal.csv"} };

  TableReader op(coldefs, "csv", extra, 100);
  EXPECT_EQ(NO_ERR, op.run());
  while (!op.out_q.finished()) {
    const Records *records = op.out_q.front();
    EXPECT_NE((Records *)NULL, records);
    EXPECT_EQ(3, records->size());  // こういうインターフェイスないと使えない。そのためには、records->columnsを直接いじらせるのではだめで、適切なapiメソッドを作ってあげるべき

    EXPECT_EQ(101, GET_SMARTDB_VALUE(records->columns[0]->get(0), SmartdbInt));
    EXPECT_EQ(201, GET_SMARTDB_VALUE(records->columns[0]->get(1), SmartdbInt));
    EXPECT_EQ(301, GET_SMARTDB_VALUE(records->columns[0]->get(2), SmartdbInt));
    op.out_q.pop();
  }
}
