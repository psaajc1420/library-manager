#include "library-manager/uid.h"

#include <sstream>

#include "gtest/gtest.h"

namespace {

TEST(UIDConstructorTest, CheckStaticIdIncrease) {
  UID id1;
  EXPECT_EQ(id1.id_, 1);
  UID id2;
  EXPECT_EQ(id2.id_, 2);
}

TEST(UIDCopyConstructorTest, CheckValidity) {
  UID id1;
  UID id2 = id1;
  EXPECT_EQ(id2.id_, 3);
}

}