#include "library-manager/person.h"

#include <sstream>

#include "gtest/gtest.h"

namespace {

TEST(InsertionOperatorTest, IsCorrect) {
  Person person("Luke", "", "Skywalker");
  std::stringstream output;
  output << person;
  EXPECT_TRUE(output.str() == "Luke  Skywalker");
}

}