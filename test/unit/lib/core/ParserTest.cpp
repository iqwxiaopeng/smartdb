/*
 * ParserTest.cpp
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#include "gtest/gtest.h"
#include "core/Parser.h"
#include "ast/Root.h"
#include "ast/SelectStatement.h"

#define ast_root Ast::Root::ast_root

using namespace Smartdb;

class ParserTest : public ::testing::Test {
protected:
  virtual void SetUp() {
  }
};

TEST_F(ParserTest, success_select_001) {
  const char * sql = "SELECT * FROM T;";
  ASSERT_NO_THROW(Parser _(sql));

  Parser _(sql);
  EXPECT_EQ(ast_root->root_type, Ast::SELECT_STATEMENT);
  Ast::SelectStatement * select_stmt = (Ast::SelectStatement *)ast_root->root_node;
  EXPECT_TRUE(select_stmt->select_list_all);
}
