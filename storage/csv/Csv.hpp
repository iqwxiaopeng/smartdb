/*
 * Csv.h
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#ifndef STORAGE_CSV_H_
#define STORAGE_CSV_H_

#include <unordered_map>
#include "PartialCsvParser.hpp"
#include "api/SmartdbStorage.hpp"

namespace Smartdb { class Logger; }

typedef struct csv_storage_t {
  Smartdb::Logger * logger;
  PCP::CsvConfig * csv_config;
  PCP::PartialCsvParser * parser;
  std::unordered_map<std::string, size_t> col_index;  // { "col1" => 0, ... }
} csv_storage_t;

/**
 *
 * @param logger
 * @param extra
 * @return csv_storage_t * casted to void *. Pass this return value to storage_finish(). NULL on error.
 */
extern "C" void *storage_init(
  Smartdb::Logger * const logger,
  const std::unordered_map<std::string, std::string> &extra);

/**
 * Reads up to \p n_records_chunk from CSV file specified at storage_init() and push the them into \p records.
 * @param[in] csv_storage Return value of storage_init().
 * @param[in] n_records_chunk Maximum number of records to read at a time.
 * @param[out] records Have ColumnDef array to specify records type.  Also records data will be stored in this param.
 * @param[out] n_read_records Number of records read. Can take 0 ~ \p n_records_chunk
 * @param[out] finished When records to read no longer remain, this flag will be true.
 */
extern "C" SmartdbErr storage_read_records(
  const void * const csv_storage,
  size_t n_records_chunk,
  /* out */
  Smartdb::Records &records,
  size_t& read_records,
  bool& finished);

/**
 * @param csv_storage Return value of storage_init().
 */
extern "C" void storage_finish(void * csv_storage);

/**
 * Push a \p row to \p records.
 * @param[in] csv_storage Return value of storage_init().
 * @param[in] row
 * @param[out] records
 */
static SmartdbErr _fill_a_row(
  const void * const csv_storage,
  const std::vector<std::string> & row,
  /* out */
  Smartdb::Records & records);

  #endif /* STORAGE_CSV_H_ */
