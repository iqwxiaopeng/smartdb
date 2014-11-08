#include "gtest/gtest.h"
#include "datastruct/Record.h"
#include "datastruct/Buffer.h"

using namespace Smartdb;

const size_t bufsz = 1024;
Buffer buf(bufsz);

TEST(hello, first) {
  EXPECT_EQ(Smartdb::hello(), 777);
}
TEST(hello, second) {
  EXPECT_EQ(Smartdb::hello(), 888);
}

TEST(a, b) {
  Record rec(buf);
  //rec.add(123, );
}
