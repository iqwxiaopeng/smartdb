/*
 * StorageEngineLib.hpp
 *
 *  Created on: 2015/01/06
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_OP_STORAGEENGINELIB_HPP_
#define INCLUDE_OP_STORAGEENGINELIB_HPP_

#include "api/SmartdbStorage.hpp"
#include "hack/DynamicLib.hpp"

/**
 * Life-cycle of a storage engine.
 */
typedef struct storage_engine_lib_t {
  lib_t dlib_handler;
  storage_funcs_t storage_funcs;
  void * storage_status;
} storage_engine_lib_t;


#endif /* INCLUDE_OP_STORAGEENGINELIB_HPP_ */
