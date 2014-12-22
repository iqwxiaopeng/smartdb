#ifndef INCLUDE_OP_TABLE_READER_H_
#define INCLUDE_OP_TABLE_READER_H_

#include <string>
#include <vector>
#include <unordered_map>
#include "storageinterface/ColumnDef.h"
#include "api/SmartdbType.h"
#include "op/Operator.h"
#include "op/OperatorParam.h"
#include "hack/Class.h"

namespace Smartdb {

class TableReader : public Operator {
public:
  TableReader(const OperatorParam * const param);
  ~TableReader();

  SmartdbErr run(const Scheduler & scheduler);

private:
  const TableReaderParam * const param;
  lib_t dlib_handler;
  storage_funcs_t storage_funcs;

  SmartdbErr read();
  std::string dlib_name_without_suffix();
  void load_dlib_funcs();
  void unload_dlib_funcs();

PREVENT_CLASS_DEFAULT_METHODS(TableReader);
};

}

#endif /* INCLUDE_OP_TABLE_READER_H_ */
