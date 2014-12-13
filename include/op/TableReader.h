#ifndef INCLUDE_OP_TABLE_READER_H_
#define INCLUDE_OP_TABLE_READER_H_

#include <string>
#include <vector>
#include <unordered_map>
#include "storageinterface/ColumnDef.h"
#include "api/SmartdbType.h"
#include "op/StreamOperator.h"
#include "hack/Class.h"

namespace Smartdb {

class TableReader : public StreamOperator {
public:
  TableReader(
    const std::vector<const ColumnDef *> &coldefs,
    const std::string& storage_engine_name,
    const std::unordered_map<std::string, std::string> &extra,
    size_t n_records_to_read);
  ~TableReader();

  SmartdbErr run(Scheduler * const scheduler);

private:
  SmartdbErr read();
  std::string dlib_name_without_suffix();
  void load_dlib_funcs();
  void unload_dlib_funcs();

  // TableReader is always at least RUNNABLE.
  // And no one call this function.
  void got_input_records(const Operator * const child_op) {}

  const std::vector<const ColumnDef *> &coldefs;
  const std::unordered_map<std::string, std::string> &extra;
  std::string storage_engine_name;
  lib_t dlib_handler;
  storage_funcs_t storage_funcs;
  size_t n_records_to_read;

PREVENT_CLASS_DEFAULT_METHODS(TableReader);
};

}

#endif /* INCLUDE_OP_TABLE_READER_H_ */
