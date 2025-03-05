cmake_minimum_required(VERSION 3.10)
project(JSONParser VERSION 1.0 LANGUAGES CXX)

# Use C++17 (or later)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories (public headers)
include_directories(include)

# Add library target
add_library(json_parser STATIC src/json_parser.cpp)

# Define test executable (optional)
add_executable(json_parser_tests tests/json_parser_test.cpp)

# Link the test executable with the library
target_link_libraries(json_parser_tests json_parser)

# Enable testing (if using CTest)
enable_testing()
add_test(NAME JSONParserTest COMMAND json_parser_tests)
