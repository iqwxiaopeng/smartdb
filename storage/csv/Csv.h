/*
 * Csv.h
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#ifndef STORAGE_CSV_H_
#define STORAGE_CSV_H_

#include "api/SmartdbStorage.h"

extern "C"
void *storage_init(
  Smartdb::Logger * const logger,
  const std::unordered_map<std::string, std::string> &extra);

/**
 * Reads records from CSV file specified at storage_init().
 * @param n_records_chunk Maximum number of records to read at a time.
 * @param records Have ColumnDef array to specify records type.  Also records data will be stored in this param.
 * @param read_records How many records are read actually.
 * @param finished When records to read no longer remain, this flag will be true.
 */
extern "C" void *storage_read_records(
  size_t n_records_chunk,
  /* out */
  Smartdb::Records &records,
  size_t n_records,
  size_t& read_records,
  bool& finished);

extern "C"
void *storage_finish();

void set_special_chars();
void set_col_index();

#endif /* STORAGE_CSV_H_ */
