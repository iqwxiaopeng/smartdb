/*
 * Csv.cpp
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#include <cstdio>
#include <cstring>
#include <cerrno>
#include <PartialCsvParser.hpp>
#include "Csv.hpp"
#include "api/SmartdbType.hpp"
#include "hack/Assert.hpp"

void* storage_init(
  Smartdb::Logger* const _logger,
  const std::unordered_map<std::string, std::string> &extra)
{
  csv_storage_t * csv_storage = new csv_storage_t;
  csv_storage->logger = _logger;

  const std::string & csv_path = extra.at("path");

  // instantiate CsvConfig
  try {
    csv_storage->csv_config = new PCP::CsvConfig(csv_path.c_str());
  } catch (PCP::PCPError & e) {
    csv_storage->logger->error(e.what());
    return NULL;
  }

  // initialize col_index
  std::vector<std::string> headers = csv_storage->csv_config->get_headers();
  for (size_t i = 0; i < headers.size(); ++i)
    csv_storage->col_index[headers[i]] = i;

  // [TODO] - multi thread
  csv_storage->parser = new PCP::PartialCsvParser(*csv_storage->csv_config);

  return (void *)csv_storage;
}

void storage_finish(void * csv_storage) {
  csv_storage_t * _csv_storage = (csv_storage_t *)csv_storage;
  ASSERT(_csv_storage);
  ASSERT(_csv_storage->csv_config);
  ASSERT(_csv_storage->parser);

  delete _csv_storage->csv_config;
  delete _csv_storage->parser;
  delete _csv_storage;
}

SmartdbErr storage_read_records(
  const void * const csv_storage,
  size_t n_records_chunk,
  /* out */
  Smartdb::Records& records,
  size_t& n_read_records,
  bool& finished)
{
  ASSERT(csv_storage);
  ASSERT(n_records_chunk > 0);
  const csv_storage_t * const _csv_storage = (csv_storage_t *)csv_storage;

  finished = false;
  n_read_records = 0;
  std::vector<std::string> row;

  for ( ; n_read_records < n_records_chunk; ++n_read_records) {
    if ((row = _csv_storage->parser->get_row()).empty()) {
      finished = true;
      break;
    }
    SmartdbErr ret;
    if ((ret = _fill_a_row(_csv_storage, row, records)) != NO_ERR) return ret;
  }

  ASSERT(0 <= n_read_records);
  ASSERT(n_read_records <= n_records_chunk);
  return NO_ERR;
}

static inline SmartdbErr _fill_a_row(
  const void * const csv_storage,
  const std::vector<std::string> & row,
  /* out */
  Smartdb::Records & records)
{
  ASSERT(csv_storage);
  const csv_storage_t * const _csv_storage = (csv_storage_t *)csv_storage;

  for (size_t col_i = 0; col_i < records.coldefs.size(); ++col_i) {
    const Smartdb::ColumnDef *coldef = records.coldefs[col_i];
    Smartdb::Column *col = records.columns[col_i];

    std::unordered_map<std::string, size_t>::const_iterator kv;
    kv = _csv_storage->col_index.find(coldef->name);
    if (kv == _csv_storage->col_index.end()) return UNKNOWN_COLUMN;

    size_t col_index_in_csv = kv->second;
    const std::string &column_s = row[col_index_in_csv];

    col->add(str_to_SmartdbValue(column_s, coldef->type));
  }
  return NO_ERR;
}
