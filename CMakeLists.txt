# version of cmake
cmake_minimum_required(VERSION 3.9.0)

# name of the project
project(bookloans)

# set flags for compiler
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++11 -g")

# set important directories to variables
set(bookloans_bin_dir "${CMAKE_SOURCE_DIR}/bin")
set(bookloans_build_include_dirs
    "${CMAKE_SOURCE_DIR}/src")

# Bring the headers from the include directory
include_directories(${bookloans_build_include_dirs})

set(source_files
  src/library-manager/person.cpp
  src/library-manager/borrower.cpp
  src/library-manager/author.cpp
  src/library-manager/date.cpp
  src/library-manager/uid.cpp
  src/library-manager/book.cpp
  src/library-manager/library_manager.cpp
)

set(test_files
  src/library-manager/person_unittest.cpp
  src/library-manager/library_manager_unittest.cpp
  src/library-manager/date_unittest.cpp
  src/library-manager/uid_unittest.cpp
)

# Add all files in src directory
add_executable(main.out test/main.cpp ${source_files})


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(
  tests
  ${test_files}
  ${source_files}
)
target_link_libraries(tests gtest_main)

set_target_properties(tests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${bookloans_bin_dir}"
)

set_target_properties(main.out
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${bookloans_bin_dir}"
)

# creates a list of file paths to add to the make_clean variable
list(APPEND clean_files "${bookloans_bin_dir}/book_shelf.txt")
list(APPEND clean_files "${bookloans_bin_dir}/books_on_loan.txt")

# Add files from bin to the "make clean" command
set_directory_properties(PROPERTIES 
  ADDITIONAL_MAKE_CLEAN_FILES "${clean_files}"
)