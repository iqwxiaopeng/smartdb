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
  ~TableReader();

  SmartdbErr run();

private:
  SmartdbErr read();
  std::string dlib_name();
  void load_dlib_funcs();
  void unload_dlib_funcs();

  std::string storage_engine_name;
  lib_t dlib_handler;
  storage_funcs_t storage_funcs;

PREVENT_CLASS_DEFAULT_METHODS(TableReader);
};

}

#endif /* INCLUDE_OP_TABLE_READER_H_ */
