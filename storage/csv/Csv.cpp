/*
 * Csv.cpp
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#include <stdio.h>
#include <unordered_map>
#include "Csv.h"
#include "hack/Assert.h"

// [TODO] - use thread local storage
Smartdb::Logger * logger = 0;
FILE *csv_fp = 0;

void* storage_init(
  Smartdb::Logger* const _logger,
  const std::unordered_map<std::string, std::string> &extra) {
  logger = _logger;

  csv_fp = fopen(extra.at("path").c_str(), "r");

  return 0;
}

void* storage_read_records(Smartdb::Records& records, size_t n_records) {
/*  FILE *fp = fopen()
  fread();
  //freadでread_buf埋める


  lines in read_buf.readline()
      cols in lines.split(',')
        size_t col_idx;
        for (size_t i = 0; i < records.coldefs.size(); ++i)
          col_idx = cols.search(records.coldefs[i].name);
        records.columns[col_idx]->add(cols[col_idx]);
        */
  return 0;
}

void* storage_finish() {
  fclose(csv_fp);
}
