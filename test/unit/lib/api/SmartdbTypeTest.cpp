#include "SmartdbTest.hpp"
#include "api/SmartdbType.hpp"

using namespace Smartdb;

class SmartdbTypeTest : public SmartdbTest {
protected:
  SmartdbTypeTest() {}

  virtual void SetUp() {}
};

TEST_F(SmartdbTypeTest, SMARTDB_SIZEOF) {
  EXPECT_EQ(4UL, SMARTDB_SIZEOF(SMARTDB_INT));
  EXPECT_EQ(8UL, SMARTDB_SIZEOF(SMARTDB_DOUBLE));
}
