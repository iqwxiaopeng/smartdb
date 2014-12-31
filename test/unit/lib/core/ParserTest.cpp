/*
 * ParserTest.cpp
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#include "gtest/gtest.h"
#include "core/Parser.hpp"
#include "ast/Root.hpp"
#include "ast/SelectStatement.hpp"

#define ast_root Ast::Root::ast_root

using namespace Smartdb;

class ParserTest : public ::testing::Test {
protected:
  virtual void SetUp() {
  }
};

TEST_F(ParserTest, success_select_001) {
  const char * sql = "SELECT * FROM t0;";
  ASSERT_NO_THROW(Parser _(sql));

  Parser _(sql);
  EXPECT_EQ(ast_root->root_type, Ast::SELECT_STATEMENT);
  Ast::SelectStatement * select_stmt = (Ast::SelectStatement *)ast_root->root_node;

  EXPECT_TRUE(select_stmt->is_select_list_all());

  EXPECT_EQ("t0", select_stmt->get_table());
}
TEST_F(ParserTest, success_select_002) {
  const char * sql = "SELECT c0, c1 FROM t0;";
  ASSERT_NO_THROW(Parser _(sql));

  Parser _(sql);
  EXPECT_EQ(ast_root->root_type, Ast::SELECT_STATEMENT);
  Ast::SelectStatement * select_stmt = (Ast::SelectStatement *)ast_root->root_node;

  EXPECT_FALSE(select_stmt->is_select_list_all());

  EXPECT_EQ("c0", select_stmt->fetch_select_list_column(0));
  EXPECT_EQ("c1", select_stmt->fetch_select_list_column(1));

  EXPECT_EQ("t0", select_stmt->get_table());
}
