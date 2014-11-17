/*
 * SmartdbType.h
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_API_SMARTDBTYPE_H_
#define INCLUDE_API_SMARTDBTYPE_H_

#include <stddef.h>
#include <stdint.h>

enum SmartdbType {
  SMARTDB_INT = 0,
};
typedef int32_t SmartdbInt;

enum SmartdbErr {
  NO_ERR = 0,
  PHYSICAL_MEM_SHORTAGE,  // Cannot allocate memory
  MEM_BUF_SHORTAGE,       // `Buffer` space is not enough
};

#endif /* INCLUDE_API_SMARTDBTYPE_H_ */
