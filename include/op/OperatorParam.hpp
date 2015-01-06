/*
 * OperatorParam.h
 *
 *  Created on: 2014/12/22
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_OP_OPERATORPARAM_H_
#define INCLUDE_OP_OPERATORPARAM_H_

#include <vector>
#include <string>
#include <unordered_map>
#include "storageinterface/ColumnDef.hpp"
#include "op/StorageEngineLib.hpp"

namespace Smartdb {

typedef struct OperatorParam {} OperatorParam;

typedef struct TableReaderParam : OperatorParam {
  const std::vector<const ColumnDef *> &coldefs;
  storage_engine_lib_t * engine;
  size_t records_chunk_size;

  /**
   * Parameters to pass to TableReader.
   * @param coldefs Column definition.
   * @param engine Return value of TableReader::init_storage_engine().
   * @param records_chunk_size Number of records to read from storage engine. Storage engine should memorize how many records are already read.
   */
  TableReaderParam(
    const std::vector<const ColumnDef *> &coldefs,
    storage_engine_lib_t * engine,
    size_t records_chunk_size)
  : coldefs(coldefs), engine(engine), records_chunk_size(records_chunk_size)
  {}

} TableReaderParam;

} /* namespace Smartdb */

#endif /* INCLUDE_OP_OPERATORPARAM_H_ */
