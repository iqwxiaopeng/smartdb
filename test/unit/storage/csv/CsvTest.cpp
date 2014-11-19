#include "gtest/gtest.h"
#include <unordered_map>
#include "csv/Csv.h"
#include "log/StderrLogger.h"
#include "hack/Assert.h"

using namespace Smartdb;

class CsvTest : public ::testing::Test {
protected:
  StderrLogger logger;
  std::unordered_map<std::string, std::string> extra;

  virtual void SetUp() {
  }
  virtual void TearDown() {
    storage_finish();
  }
};

TEST_F(CsvTest, reads_1record_from_CSV) {
  extra["path"] = "fixture/storage_csv_normal.csv";
  EXPECT_EQ((void *)NO_ERR, storage_init(&logger, extra));

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
  EXPECT_EQ((void *)NO_ERR, storage_read_records(records, 1, read_records, finished));

  EXPECT_FALSE(finished);
  EXPECT_EQ(1, read_records);

  EXPECT_EQ(101, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(102, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbInt));
}
TEST_F(CsvTest, reads_3records_from_CSV) {
  extra["path"] = "fixture/storage_csv_normal.csv";
  EXPECT_EQ((void *)NO_ERR, storage_init(&logger, extra));

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
  EXPECT_EQ((void *)NO_ERR, storage_read_records(records, 3, read_records, finished));

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
  extra["path"] = "fixture/storage_csv_normal.csv";
  EXPECT_EQ((void *)NO_ERR, storage_init(&logger, extra));

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
  EXPECT_EQ((void *)NO_ERR, storage_read_records(records, 4, read_records, finished));

  EXPECT_TRUE(finished);
  EXPECT_EQ(3, read_records);

  EXPECT_EQ(101, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(102, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbInt));

  EXPECT_EQ(201, GET_SMARTDB_VALUE(records.columns[0]->get(1), SmartdbInt));
  EXPECT_EQ(202, GET_SMARTDB_VALUE(records.columns[1]->get(1), SmartdbInt));

  EXPECT_EQ(301, GET_SMARTDB_VALUE(records.columns[0]->get(2), SmartdbInt));
  EXPECT_EQ(302, GET_SMARTDB_VALUE(records.columns[1]->get(2), SmartdbInt));
}
TEST_F(CsvTest, reads_1column_from_2columns) {
  extra["path"] = "fixture/storage_csv_normal.csv";
  EXPECT_EQ((void *)NO_ERR, storage_init(&logger, extra));

  const ColumnDef coldef("col2", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(1, 0);
  coldefs[0] = &coldef;

  Buffer colbuf(1024);
  std::vector<Buffer *> colbufs(1, 0);
  colbufs[0] = &colbuf;

  Records records(coldefs, colbufs);

  size_t read_records;
  bool finished;
  EXPECT_EQ((void *)NO_ERR, storage_read_records(records, 1, read_records, finished));

  EXPECT_FALSE(finished);
  EXPECT_EQ(1, read_records);

  EXPECT_EQ(102, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
}
TEST_F(CsvTest, reads_twice) {
  extra["path"] = "fixture/storage_csv_normal.csv";
  EXPECT_EQ((void *)NO_ERR, storage_init(&logger, extra));

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

  // 1st
  EXPECT_EQ((void *)NO_ERR, storage_read_records(records, 1, read_records, finished));
  EXPECT_FALSE(finished);
  EXPECT_EQ(1, read_records);
  EXPECT_EQ(101, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(102, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbInt));

  records.clear();

  // 2nd
  EXPECT_EQ((void *)NO_ERR, storage_read_records(records, 1, read_records, finished));
  EXPECT_FALSE(finished);
  EXPECT_EQ(1, read_records);
  EXPECT_EQ(201, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(202, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbInt));
}
TEST_F(CsvTest, reads_double_value) {
  extra["path"] = "fixture/storage_csv_double.csv";
  EXPECT_EQ((void *)NO_ERR, storage_init(&logger, extra));

  const ColumnDef coldef1("col1", SMARTDB_DOUBLE);
  const ColumnDef coldef2("col2", SMARTDB_DOUBLE);
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
  EXPECT_EQ((void *)NO_ERR, storage_read_records(records, 1, read_records, finished));

  EXPECT_FALSE(finished);
  EXPECT_EQ(1, read_records);

  EXPECT_EQ(1.01, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbDouble));
  EXPECT_EQ(1.02, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbDouble));
}
TEST_F(CsvTest, column_not_found) {
  extra["path"] = "fixture/storage_csv_normal.csv";
  EXPECT_EQ((void *)NO_ERR, storage_init(&logger, extra));

  const ColumnDef coldef("col404", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(1, 0);
  coldefs[0] = &coldef;

  Buffer colbuf(1024);
  std::vector<Buffer *> colbufs(1, 0);
  colbufs[0] = &colbuf;

  Records records(coldefs, colbufs);

  size_t read_records;
  bool finished;
  EXPECT_EQ((void *)UNKNOWN_COLUMN, storage_read_records(records, 1, read_records, finished));
}
TEST_F(CsvTest, reads_from_same_column) {
  extra["path"] = "fixture/storage_csv_normal.csv";
  EXPECT_EQ((void *)NO_ERR, storage_init(&logger, extra));

  const ColumnDef coldef1("col1", SMARTDB_INT);
  const ColumnDef coldef2("col1", SMARTDB_INT);
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
  EXPECT_EQ((void *)NO_ERR, storage_read_records(records, 1, read_records, finished));

  EXPECT_FALSE(finished);
  EXPECT_EQ(1, read_records);

  EXPECT_EQ(101, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(101, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbInt));
}
TEST_F(CsvTest, reads_too_many_records) {
  extra["path"] = "fixture/storage_csv_normal.csv";
  EXPECT_EQ((void *)NO_ERR, storage_init(&logger, extra));

  const ColumnDef coldef1("col1", SMARTDB_INT);
  const ColumnDef coldef2("col2", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(2, 0);
  coldefs[0] = &coldef1;
  coldefs[1] = &coldef2;

  Buffer colbuf1(4);  // not enough for reading 2 columns
  Buffer colbuf2(1024);
  std::vector<Buffer *> colbufs(2, 0);
  colbufs[0] = &colbuf1;
  colbufs[1] = &colbuf2;

  Records records(coldefs, colbufs);

  size_t read_records;
  bool finished;
  EXPECT_EQ((void *)NO_ERR, storage_read_records(records, 2, read_records, finished));

  EXPECT_FALSE(finished);
  EXPECT_EQ(1, read_records);

  EXPECT_EQ(101, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(102, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbInt));
}
TEST_F(CsvTest, reread_after_reading_too_many_records) {
  extra["path"] = "fixture/storage_csv_normal.csv";
  EXPECT_EQ((void *)NO_ERR, storage_init(&logger, extra));

  const ColumnDef coldef1("col1", SMARTDB_INT);
  const ColumnDef coldef2("col2", SMARTDB_INT);
  std::vector<const ColumnDef *> coldefs(2, 0);
  coldefs[0] = &coldef1;
  coldefs[1] = &coldef2;

  Buffer colbuf1(4);  // not enough for reading 2 columns
  Buffer colbuf2(1024);
  std::vector<Buffer *> colbufs(2, 0);
  colbufs[0] = &colbuf1;
  colbufs[1] = &colbuf2;

  Records records(coldefs, colbufs);

  size_t read_records;
  bool finished;

  EXPECT_EQ((void *)NO_ERR, storage_read_records(records, 2, read_records, finished));
  EXPECT_FALSE(finished);
  EXPECT_EQ(1, read_records);
  EXPECT_EQ(101, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(102, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbInt));

  records.clear();
  EXPECT_EQ((void *)NO_ERR, storage_read_records(records, 2, read_records, finished));
  EXPECT_FALSE(finished);
  EXPECT_EQ(1, read_records);
  EXPECT_EQ(201, GET_SMARTDB_VALUE(records.columns[0]->get(0), SmartdbInt));
  EXPECT_EQ(202, GET_SMARTDB_VALUE(records.columns[1]->get(0), SmartdbInt));
}
TEST_F(CsvTest, csv_file_not_found) {
  extra["path"] = "fixture/storage_csv_normal.csv............exe";
  EXPECT_EQ((void *)IO_ERR, storage_init(&logger, extra));
}
