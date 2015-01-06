#ifndef INCLUDE_OP_TABLE_READER_H_
#define INCLUDE_OP_TABLE_READER_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "api/SmartdbStorage.hpp"
#include "op/Operator.hpp"
#include "op/OperatorParam.hpp"
#include "hack/Class.hpp"
#include "hack/DynamicLib.hpp"

namespace Smartdb {

class TableReader : public Operator {

//
// Static members
public:
  /**
   * Initialize storage engine.
   * @param storage_engine_name Specify "foobar" if engine's file name is "libsmartdb_engine_foobar.(so|dylib)".
   * @param extra Storage engine specific parameters.
   * @return Storage engine specific state. Pass this to finish_storage_engine() when finished.
   * @note Don't forget to call finish_storage_engine() to release allocated heap inside storage engine.
   */
  static storage_engine_lib_t * init_storage_engine(
    const std::string & storage_engine_name,
    const std::unordered_map<std::string, std::string> & extra);

  /**
   * Finish storage engine.
   * @param p Return value of init_storage_engine().
   */
  static void finish_storage_engine(storage_engine_lib_t * p);

private:
  static std::string dlib_name_without_suffix(const std::string & storage_engine_name);

  /**
   *
   * @param[in] storage_engine_name Specify "foobar" if engine's file name is "libsmartdb_engine_foobar.(so|dylib)".
   * @param[out] dlib_handler Pass to unload_dlib_funcs() to prevent memory leak.
   * @param[out] storage_funcs Pointers to storage engine functions.
   * @note Don't forget to
   */
  static void load_dlib_funcs(
    const std::string & storage_engine_name,
    /*out*/
    lib_t * dlib_handler,
    storage_funcs_t * storage_funcs);

  static void unload_dlib_funcs(lib_t dlib_handler);

//
// Non-static members
public:
  TableReader(const OperatorParam * const param);
  ~TableReader();

  SmartdbErr run(const Scheduler & scheduler);

private:
  const TableReaderParam * const param;

  SmartdbErr read();

PREVENT_CLASS_DEFAULT_METHODS(TableReader);
};

}

#endif /* INCLUDE_OP_TABLE_READER_H_ */
