/*
 * Schema.h
 *
 *  Created on: 2014/12/03
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_DATASTRUCT_SCHEMA_H_
#define INCLUDE_DATASTRUCT_SCHEMA_H_

#include <string>
#include <unordered_map>
#include "api/SmartdbType.hpp"
#include "hack/Class.hpp"

namespace Smartdb {

class Schema {
public:
  Schema(const char * const db_file);
  virtual ~Schema();

  SmartdbErr load(const char * const table_name);

  const std::string & storage_engine_name() const;
  std::unordered_map<std::string, std::string> & extra();

private:
  std::string _storage_engine_name;
  std::unordered_map<std::string, std::string> _extra;

  PREVENT_CLASS_DEFAULT_METHODS(Schema);
};

} /* namespace Smartdb */

#endif /* INCLUDE_DATASTRUCT_SCHEMA_H_ */
