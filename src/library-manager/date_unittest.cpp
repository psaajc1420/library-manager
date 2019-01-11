#include "library-manager/date.h"

#include <sstream>

#include "gtest/gtest.h"

namespace {

TEST(DateTest, CheckGetDate) {
  Date date(7, 10, 2001);
  date.GetDate();
  EXPECT_TRUE(date.GetDate() == "2001107");
}

}