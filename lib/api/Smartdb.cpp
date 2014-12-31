/*
 * Smartdb.cpp
 *
 *  Created on: 2014/11/07
 *      Author: nakatani.sho
 */

#include <cstdlib>
#include "api/Smartdb.hpp"
#include "ast/Root.hpp"
#include "ast/SelectStatement.hpp"
#include "core/Parser.hpp"
#include "datastruct/Schema.hpp"
#include "log/Logger.hpp"
#include "log/StderrLogger.hpp"

namespace Smartdb {

Logger *logger = 0;

} /* namespace Smartdb */

void smartdb_init() {
  // sets logger
#if Logger == Stderr
  Smartdb::logger = new Smartdb::StderrLogger();
#else
  Smartdb::logger = new Smartdb::StderrLogger();
#endif
}
void smartdb_finish() {
  if (Smartdb::logger) delete Smartdb::logger;
}

extern "C"
SmartdbErr smartdb_open(
  const char* db_file,
  /* out */
  smartdb** db)
{
  *db = (smartdb *)std::malloc(sizeof(smartdb));
  if (!(*db)) return PHYSICAL_MEM_SHORTAGE;

  (*db)->schema = new Smartdb::Schema(db_file);
  return NO_ERR;
}

extern "C"
void smartdb_close(smartdb* db) {
  delete db->schema;
  std::free(db);
}

extern "C"
SmartdbErr smartdb_prepare(
  smartdb* db, const char* sql,
  /* out */
  smartdb_stmt** stmt)
{
  Smartdb::Parser parser(sql);

  // [TODO] - Analyze AST, create plan tree
  ASSERT(Smartdb::Ast::Root::ast_root->root_type == Smartdb::Ast::SELECT_STATEMENT);

  Smartdb::Ast::SelectStatement * select_stmt = (Smartdb::Ast::SelectStatement *)Smartdb::Ast::Root::ast_root->root_node;

  ASSERT(select_stmt->is_select_list_all());

  // ASTからPlan Treeにコンパイルする。
  // Plan Treeの中には当然TableReaderOpも含まれるが、そのTableReaderOpの中に
  // どのテーブルのどのカラムから読むかという情報を含める

  // [TODO] - num column from AST, type from schema

/*  ColumnDef coldef(select_stmt->fetch_select_list_column(0), SMARTDB_INT);

  EXPECT_EQ("c0", select_stmt->fetch_select_list_column(0));
  EXPECT_EQ("c1", select_stmt->fetch_select_list_column(1));

  EXPECT_EQ("t0", select_stmt->get_table());*/


  return NO_ERR;
}

extern "C"
SmartdbErr smartdb_step(smartdb_stmt* stmt) {
  //

  return NO_ERR;
}

extern "C"
SmartdbInt smartdb_column_int(smartdb_stmt* stmt, unsigned int i_col) {
  return 777;
}

extern "C"
SmartdbDouble smartdb_column_double(smartdb_stmt* stmt, unsigned int i_col) {
  return 3.14;
}

SmartdbErr smartdb_finalize(smartdb_stmt* stmt) {
  return NO_ERR;
}
