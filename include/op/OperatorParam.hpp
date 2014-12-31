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

namespace Smartdb {

class ColumnDef;

typedef struct OperatorParam {} OperatorParam;

typedef struct TableReaderParam : OperatorParam {
  const std::vector<const ColumnDef *> &coldefs;
  const std::string& storage_engine_name;
  const std::unordered_map<std::string, std::string> &extra;
  size_t records_chunk_size;

  TableReaderParam(
    const std::vector<const ColumnDef *> &coldefs,
    const std::string& storage_engine_name,
    const std::unordered_map<std::string, std::string> &extra,
    size_t records_chunk_size)
  : coldefs(coldefs), storage_engine_name(storage_engine_name), extra(extra), records_chunk_size(records_chunk_size)
  {}
} TableReaderParam;

} /* namespace Smartdb */

#endif /* INCLUDE_OP_OPERATORPARAM_H_ */
