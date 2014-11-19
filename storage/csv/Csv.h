/*
 * Csv.h
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#ifndef STORAGE_CSV_H_
#define STORAGE_CSV_H_

#include "api/Smartdb.h"

extern "C"
void *storage_init(
  Smartdb::Logger * const logger,
  const std::unordered_map<std::string, std::string> &extra);

extern "C"
void *storage_read_records(
  Smartdb::Records &records,
  size_t n_records,
  size_t &read_records,
  bool &finished);

extern "C"
void *storage_finish();

void set_parser(const std::string &path);
void set_col_index();

#endif /* STORAGE_CSV_H_ */
