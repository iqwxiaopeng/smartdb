/*
 * Select.h
 *
 *  Created on: 2014/11/23
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_AST_SELECTSTATEMENT_H_
#define INCLUDE_AST_SELECTSTATEMENT_H_

#include <string>
#include <vector>
#include "Node.hpp"
#include "hack/Assert.hpp"

namespace Smartdb {
namespace Ast {

class SelectStatement : public Node {
public:
  SelectStatement();
  virtual ~SelectStatement();

  bool is_select_list_all() const {
    return select_list_all;
  }
  void set_select_list_all(bool v) {
    select_list_all = v;
  }

  void append_select_list_column(const char * const colname) {
    colnames.push_back(std::string(colname));
  }
  const std::string & fetch_select_list_column(size_t index) const {
    ASSERT(index < colnames.size());
    return colnames[index];
  }

  const std::string& get_table() const {
    return table;
  }
  void set_table(const std::string& table) {
    this->table = table;
  }

private:
  bool select_list_all;  // true when `SELECT * FROM ...`
  std::vector<std::string> colnames;
  std::string table;  // [TODO] - should have list of joined-table (see BNF)
};

}
} /* namespace Smartdb */

#endif /* INCLUDE_AST_SELECTSTATEMENT_H_ */
