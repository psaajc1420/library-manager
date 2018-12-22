# version of cmake
cmake_minimum_required(VERSION 3.9.0)

# name of the project
project(bookloans)

# set flags for compiler
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

# set important directories to variables
set(bookloans_bin_dir "${CMAKE_SOURCE_DIR}/bin")
set(bookloans_build_include_dirs
    "${CMAKE_SOURCE_DIR}/src")

# Bring the headers from the include directory
include_directories(${bookloans_build_include_dirs})

file(GLOB SOURCES
    "src/book.cpp"
    "src/date.cpp"
    "src/library_manager.cpp"
)

# Add all files in src directory
add_executable(main.out test/main.cpp ${SOURCES})

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