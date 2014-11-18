#ifndef INCLUDE_OP_TABLE_READER_H_
#define INCLUDE_OP_TABLE_READER_H_

#include <string>
#include "api/SmartdbType.h"
#include "op/Operator.h"
#include "hack/Class.h"

namespace Smartdb {

class TableReader : public Operator {
public:
  TableReader(const std::string &storage_engine_name);

  void read();

private:
  std::string storage_engine_name;
  lib_t lib_handler;

PREVENT_CLASS_DEFAULT_METHODS(TableReader);
};

}

#endif /* INCLUDE_OP_TABLE_READER_H_ */
