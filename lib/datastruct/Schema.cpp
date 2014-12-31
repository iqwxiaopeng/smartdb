/*
 * Schema.cpp
 *
 *  Created on: 2014/12/03
 *      Author: nakatani.sho
 */

#include "datastruct/Schema.hpp"

namespace Smartdb {

Schema::Schema(const char* const db_file)
{
  // [TODO] - everything
  _storage_engine_name = "csv";
  _extra["path"] = "/Users/nakatani.sho/git/smartdb/test/unit/fixture/storage_csv_normal.csv";
}

Schema::~Schema() {
}

SmartdbErr Schema::load(const char* const table_name) {
  return NO_ERR;
}

const std::string& Schema::storage_engine_name() const {
  return _storage_engine_name;
}

std::unordered_map<std::string, std::string>& Schema::extra() {
  return _extra;
}

} /* namespace Smartdb */
