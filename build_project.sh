#!/bin/bash

# Delete the build directory if it exists
rm -rf build

# Recreate the build directory and navigate into it
mkdir build && cd build

# Reconfigure the project with Debug mode
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build the project
cmake --build .

cd Debug
./json_parser_tests.exe

