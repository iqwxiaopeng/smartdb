/*
 * Smartdb.h
 *
 * To be included by storage engines.
 *
 *  Created on: 2014/11/07
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_API_SMARTDB_H_
#define INCLUDE_API_SMARTDB_H_

//
// includes
#include "api/SmartdbType.h"
#include "datastruct/Records.h"  // storage engines' output
#include "mem/Buffer.h"   // storage engine implementations may use
                          // this for memory allocation
#include "datastruct/ColumnDef.h"  // storage engines use this
#include "log/Logger.h"

#endif /* INCLUDE_API_SMARTDB_H_ */
