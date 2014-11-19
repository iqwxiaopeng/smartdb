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
#include "Csv.h"
#include "api/Smartdb.h"
#include "hack/Assert.h"

// [TODO] - use thread local storage
Smartdb::Logger * logger = 0;
std::string csv_path = 0;
FILE *csv_fp = 0;
const size_t read_buf_size = 10 * 1e6;
Smartdb::Buffer *read_buf = 0;

void* storage_init(
  Smartdb::Logger* const _logger,
  const std::unordered_map<std::string, std::string> &extra) {
  logger = _logger;

  csv_path = extra.at("path");
  if (!(csv_fp = fopen(csv_path.c_str(), "r"))) {
    logger->error(strerror(errno));
    return (void *)IO_ERR;
  }

  read_buf = new Smartdb::Buffer(read_buf_size);

  return (void *)NO_ERR;
}

// limitation
// large CSV file is not supported
void* storage_read_records(Smartdb::Records& records, size_t n_records) {
  size_t ret = fread(read_buf->ptr(), read_buf_size, 1, csv_fp);
  if (ret != 0) {
    logger->warn((std::string(csv_path) + " is too large").c_str());
    return (void *)ERR;
  }
  if (ferror(csv_fp)) {
    logger->error("Something wrong while fread()");
    return (void *)IO_ERR;
  }

  const char *line_start = read_buf->ptr();
  size_t line_size;

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
  return (void *)NO_ERR;
}

// reentrant
void* storage_finish() {
  if (csv_fp) fclose(csv_fp);
  if (read_buf) delete read_buf;
  return (void *)NO_ERR;
}
