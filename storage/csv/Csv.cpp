/*
 * Csv.cpp
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unordered_map>
#include "csv_parser.hpp"
#include "Csv.h"
#include "api/Smartdb.h"
#include "hack/Assert.h"

// [TODO] - use thread local storage
Smartdb::Logger * logger = 0;
std::string csv_path;
csv_parser parser;
std::unordered_map<std::string, size_t> col_index;  // { "col1" => 0, ... }

void* storage_init(
  Smartdb::Logger* const _logger,
  const std::unordered_map<std::string, std::string> &extra) {
  logger = _logger;

  csv_path = extra.at("path");

  set_parser(csv_path);
  set_col_index();

  return (void *)NO_ERR;
}

void set_parser(const std::string &path) {
  parser.init(path.c_str());
  parser.set_enclosed_char('"', ENCLOSURE_OPTIONAL);
  parser.set_field_term_char(',');
  parser.set_line_term_char('\n');
}

void set_col_index() {
  csv_row row = parser.get_row();
  for (size_t i = 0; i < row.size(); ++i) col_index[row[i]] = i;
}

// limitation
// large CSV file is not supported
void* storage_read_records(Smartdb::Records& records, size_t n_records) {
  for (size_t rec_i = 0; rec_i < n_records && parser.has_more_rows(); ++rec_i) {
    csv_row row = parser.get_row();
    for (size_t col_i = 0; col_i < records.coldefs.size(); ++col_i) {
      const Smartdb::ColumnDef *coldef = records.coldefs[col_i];
      Smartdb::Column *col = records.columns[col_i];
      size_t col_index_in_csv = col_index[coldef->name];
      std::string &column_s = row[col_index_in_csv];

      SmartdbValue column_v = str_to_SmartdbValue(column_s, coldef->type);
      col->add(column_v);
    }
  }

  return (void *)NO_ERR;
}

// reentrant
void* storage_finish() {
  return (void *)NO_ERR;
}
