#include "gtest/gtest.h"
#include <unordered_map>
#include "csv/Csv.h"
#include "log/StderrLogger.h"
#include "hack/Assert.h"

using namespace Smartdb;

class CsvTest : public ::testing::Test {
protected:
  StderrLogger logger;
  std::string csv_path;
  std::unordered_map<std::string, std::string> extra;

  CsvTest()
  : csv_path("fixture/storage_csv_normal.csv")
  {}

  virtual void SetUp() {
    extra["path"] = csv_path;
    storage_init(&logger, extra);
  }
};

TEST_F(CsvTest, reads_1record_from_CSV) {
  const ColumnDef coldef1("col1", SMARTDB_INT);
  const ColumnDef coldef2("col2", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(2, 0);
  coldefs[0] = &coldef1;
  coldefs[1] = &coldef2;

  Buffer colbuf1(1024);
  Buffer colbuf2(1024);
  std::vector<Buffer *> colbufs(2, 0);
  colbufs[0] = &colbuf1;
  colbufs[1] = &colbuf2;

  Records records(coldefs, colbufs);

  size_t read_records;
  bool finished;
  storage_read_records(records, 1, read_records, finished);

  EXPECT_FALSE(finished);
  EXPECT_EQ(1, read_records);

  EXPECT_EQ(101, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(102, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbInt));
}
TEST_F(CsvTest, reads_3records_from_CSV) {
  const ColumnDef coldef1("col1", SMARTDB_INT);
  const ColumnDef coldef2("col2", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(2, 0);
  coldefs[0] = &coldef1;
  coldefs[1] = &coldef2;

  Buffer colbuf1(1024);
  Buffer colbuf2(1024);
  std::vector<Buffer *> colbufs(2, 0);
  colbufs[0] = &colbuf1;
  colbufs[1] = &colbuf2;

  Records records(coldefs, colbufs);

  size_t read_records;
  bool finished;
  storage_read_records(records, 3, read_records, finished);

  EXPECT_TRUE(finished);
  EXPECT_EQ(3, read_records);

  EXPECT_EQ(101, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(102, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbInt));

  EXPECT_EQ(201, GET_SMARTDB_VALUE(records.columns[0]->get(1), SmartdbInt));
  EXPECT_EQ(202, GET_SMARTDB_VALUE(records.columns[1]->get(1), SmartdbInt));

  EXPECT_EQ(301, GET_SMARTDB_VALUE(records.columns[0]->get(2), SmartdbInt));
  EXPECT_EQ(302, GET_SMARTDB_VALUE(records.columns[1]->get(2), SmartdbInt));
}
TEST_F(CsvTest, requesting_more_records_than_in_CSV_is_ok) {
  const ColumnDef coldef1("col1", SMARTDB_INT);
  const ColumnDef coldef2("col2", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(2, 0);
  coldefs[0] = &coldef1;
  coldefs[1] = &coldef2;

  Buffer colbuf1(1024);
  Buffer colbuf2(1024);
  std::vector<Buffer *> colbufs(2, 0);
  colbufs[0] = &colbuf1;
  colbufs[1] = &colbuf2;

  Records records(coldefs, colbufs);

  size_t read_records;
  bool finished;
  storage_read_records(records, 4, read_records, finished);

  EXPECT_TRUE(finished);
  EXPECT_EQ(3, read_records);

  EXPECT_EQ(101, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(102, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbInt));

  EXPECT_EQ(201, GET_SMARTDB_VALUE(records.columns[0]->get(1), SmartdbInt));
  EXPECT_EQ(202, GET_SMARTDB_VALUE(records.columns[1]->get(1), SmartdbInt));

  EXPECT_EQ(301, GET_SMARTDB_VALUE(records.columns[0]->get(2), SmartdbInt));
  EXPECT_EQ(302, GET_SMARTDB_VALUE(records.columns[1]->get(2), SmartdbInt));
}

TEST_F(CsvTest, reads_only_3rd_record_from_CSV) {
  // [TODO] - limit offset や、メモリを意識した連続 read_records() のために途中の行から読めるようにする
}

TEST_F(CsvTest, reads_too_many_records) {
  // [TODO] - Smartdb側で規定した返り値か例外を返す
}
