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
void *storage_init(Smartdb::Logger * const logger);

extern "C"
void *storage_read_records(Smartdb::Records &records, size_t n_records);

#endif /* STORAGE_CSV_H_ */
