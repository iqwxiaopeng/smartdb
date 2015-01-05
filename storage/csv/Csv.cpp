/*
 * Csv.cpp
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#include <unordered_map>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <PartialCsvParser.hpp>
#include "Csv.hpp"
#include "api/SmartdbType.hpp"
#include "hack/Assert.hpp"

// [TODO] - use thread local storage
Smartdb::Logger * logger = 0;
static std::string csv_path;
static PCP::CsvConfig * csv_config = 0;
static PCP::PartialCsvParser * parser = 0;
std::unordered_map<std::string, size_t> col_index;  // { "col1" => 0, ... }

void* storage_init(
  Smartdb::Logger* const _logger,
  const std::unordered_map<std::string, std::string> &extra) {
  logger = _logger;
  csv_path = extra.at("path");

  // instantiate CsvConfig
  try {
    csv_config = new PCP::CsvConfig(csv_path.c_str());
  } catch (PCP::PCPError & e) {
    logger->error(e.what());
    return (void *)IO_ERR;
  }

  // initialize col_index
  std::vector<std::string> headers = csv_config->get_headers();
  for (size_t i = 0; i < headers.size(); ++i)
    col_index[headers[i]] = i;

  // [TODO] - multi thread
  parser = new PCP::PartialCsvParser(*csv_config);

  return (void *)NO_ERR;
}


/**
 * @note storage_finish() is reentrant function.
 */
void* storage_finish() {
  if (csv_config) delete csv_config;
  if (parser) delete parser;
  return (void *)NO_ERR;
}

/**
 * Push a \p row to \p records.
 * @param[in] row
 * @param[out] records
 */
#define FILL_A_ROW(row, records) \
  for (size_t col_i = 0; col_i < records.coldefs.size(); ++col_i) { \
    const Smartdb::ColumnDef *coldef = records.coldefs[col_i]; \
    Smartdb::Column *col = records.columns[col_i]; \
    \
    std::unordered_map<std::string, size_t>::const_iterator kv; \
    kv = col_index.find(coldef->name); \
    if (kv == col_index.end()) return (void *)UNKNOWN_COLUMN; \
    size_t col_index_in_csv = kv->second; \
    std::string &column_s = row[col_index_in_csv]; \
    \
    col->add(str_to_SmartdbValue(column_s, coldef->type)); \
  }

/**
 * Reads up to \p n_records_chunk from CSV file and push the them into \p records.
 * @param[in] n_records_chunk Maximum number of records to read within this invocation.
 * @param[out] records
 * @param[out] n_read_records Number of records read. Can take 0 ~ \p n_records_chunk
 * @param[out] finished
 * @return SmartdbErr casted to (void *).
 */
void* storage_read_records(
  size_t n_records_chunk,
  /* out */
  Smartdb::Records& records,
  size_t& n_read_records,
  bool& finished)
{
  ASSERT(n_records_chunk > 0);

  finished = false;
  n_read_records = 0;
  std::vector<std::string> row;

  for ( ; n_read_records < n_records_chunk; ++n_read_records) {
    if ((row = parser->get_row()).empty()) {
      finished = true;
      break;
    }
    FILL_A_ROW(row, records);
  }

  ASSERT(0 <= n_read_records);
  ASSERT(n_read_records <= n_records_chunk);
  return (void *)NO_ERR;
}
