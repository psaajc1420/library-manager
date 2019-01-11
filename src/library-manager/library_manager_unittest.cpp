#include "library-manager/library_manager.h"

#include <string>

#include "gtest/gtest.h"

namespace {

TEST(LibraryManagerConstructorTest, TestExceptionIsHandled) {
  ASSERT_THROW(LibraryManager(0, nullptr), std::runtime_error); 
}

TEST(LibraryManagerReadTest, TestExceptionIsHandled) {
  LibraryManager manager;
  ASSERT_THROW(manager.Read(0, nullptr), std::runtime_error); 
}

}