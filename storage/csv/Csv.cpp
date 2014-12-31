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
#include <csv_parser/csv_parser.hpp>
#include "Csv.hpp"
#include "hack/Assert.hpp"

// [TODO] - use thread local storage
Smartdb::Logger * logger = 0;
std::string csv_path;
csv_parser parser;
std::unordered_map<std::string, size_t> col_index;  // { "col1" => 0, ... }
csv_row row_not_added;

void* storage_init(
  Smartdb::Logger* const _logger,
  const std::unordered_map<std::string, std::string> &extra) {
  logger = _logger;

  csv_path = extra.at("path");

  if (!parser.init(csv_path.c_str())) return (void *)IO_ERR;
  set_special_chars();
  set_col_index();

  return (void *)NO_ERR;
}

void set_special_chars() {
  parser.set_enclosed_char('"', ENCLOSURE_OPTIONAL);
  parser.set_field_term_char(',');
  parser.set_line_term_char('\n');
}

void set_col_index() {
  csv_row row = parser.get_row();
  for (size_t i = 0; i < row.size(); ++i) col_index[row[i]] = i;
}

#define FILL_A_RECORD(row, records) \
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
    SmartdbValue column_v = str_to_SmartdbValue(column_s, coldef->type); \
    SmartdbErr ret = col->add(column_v); \
    if (ret == MEM_BUF_SHORTAGE) { \
      row_not_added = row; \
      goto read_stops; \
    } else if (ret != NO_ERR) { \
      logger->error((std::string("Column::add() returns error: ") + smartdb_errmsg(ret)).c_str()); \
      return (void *)ret; \
    } \
  }


void* storage_read_records(
  Smartdb::Records& records,
  size_t n_records,
  size_t& read_records,
  bool& finished)
{
  finished = false;
  read_records = 0;

  if (!row_not_added.empty()) {
    FILL_A_RECORD(row_not_added, records);
    ++read_records;
    row_not_added.clear();
  }

  for ( ; read_records < n_records && parser.has_more_rows(); ++read_records) {
    csv_row row = parser.get_row();
    FILL_A_RECORD(row, records);
  }
read_stops:
  if (read_records == 0) return (void *)MEM_BUF_SHORTAGE;
  if (!parser.has_more_rows() && row_not_added.empty()) finished = true;

  return (void *)NO_ERR;
}

// reentrant
void* storage_finish() {
  parser.reset_record_count();
  row_not_added.clear();
  return (void *)NO_ERR;
}
