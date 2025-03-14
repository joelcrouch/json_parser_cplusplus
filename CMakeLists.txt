cmake_minimum_required(VERSION 3.10)
project(JSONParser VERSION 1.0 LANGUAGES CXX)

# Use C++17 (or later)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add library target FIRST
add_library(json_parser STATIC src/json_parser.cpp)

# THEN set include directories for it
target_include_directories(json_parser
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Define test executable
add_executable(json_parser_tests tests/json_parser_test.cpp)

# Ensure the include directory is available to the test target
target_include_directories(json_parser_tests
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Link the test executable with the library
target_link_libraries(json_parser_tests json_parser)

# Enable testing (if using CTest)
enable_testing()
add_test(NAME JSONParserTest COMMAND json_parser_tests)
