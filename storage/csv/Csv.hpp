/*
 * Csv.h
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#ifndef STORAGE_CSV_H_
#define STORAGE_CSV_H_

#include "api/SmartdbStorage.hpp"

/**
 *
 * @param logger
 * @param extra
 */
extern "C" void *storage_init(
  Smartdb::Logger * const logger,
  const std::unordered_map<std::string, std::string> &extra);

/**
 * Reads up to \p n_records_chunk from CSV file specified at storage_init() and push the them into \p records.
 * @param[in] n_records_chunk Maximum number of records to read at a time.
 * @param[out] records Have ColumnDef array to specify records type.  Also records data will be stored in this param.
 * @param[out] n_read_records Number of records read. Can take 0 ~ \p n_records_chunk
 * @param[out] finished When records to read no longer remain, this flag will be true.
 */
extern "C" SmartdbErr storage_read_records(
  size_t n_records_chunk,
  /* out */
  Smartdb::Records &records,
  size_t& read_records,
  bool& finished);

/**
 * @note storage_finish() is reentrant function.
 */
extern "C" void storage_finish();

/**
 * Push a \p row to \p records.
 * @param[in] row
 * @param[out] records
 */
static SmartdbErr _fill_a_row(const std::vector<std::string> & row, Smartdb::Records & records);

  #endif /* STORAGE_CSV_H_ */
