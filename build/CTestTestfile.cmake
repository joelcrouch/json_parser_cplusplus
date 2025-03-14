# CMake generated Testfile for 
# Source directory: C:/Users/joelc/OneDrive/Desktop/c++jsonparser
# Build directory: C:/Users/joelc/OneDrive/Desktop/c++jsonparser/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(JSONParserTest "C:/Users/joelc/OneDrive/Desktop/c++jsonparser/build/Debug/json_parser_tests.exe")
  set_tests_properties(JSONParserTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/joelc/OneDrive/Desktop/c++jsonparser/CMakeLists.txt;31;add_test;C:/Users/joelc/OneDrive/Desktop/c++jsonparser/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(JSONParserTest "C:/Users/joelc/OneDrive/Desktop/c++jsonparser/build/Release/json_parser_tests.exe")
  set_tests_properties(JSONParserTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/joelc/OneDrive/Desktop/c++jsonparser/CMakeLists.txt;31;add_test;C:/Users/joelc/OneDrive/Desktop/c++jsonparser/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(JSONParserTest "C:/Users/joelc/OneDrive/Desktop/c++jsonparser/build/MinSizeRel/json_parser_tests.exe")
  set_tests_properties(JSONParserTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/joelc/OneDrive/Desktop/c++jsonparser/CMakeLists.txt;31;add_test;C:/Users/joelc/OneDrive/Desktop/c++jsonparser/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(JSONParserTest "C:/Users/joelc/OneDrive/Desktop/c++jsonparser/build/RelWithDebInfo/json_parser_tests.exe")
  set_tests_properties(JSONParserTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/joelc/OneDrive/Desktop/c++jsonparser/CMakeLists.txt;31;add_test;C:/Users/joelc/OneDrive/Desktop/c++jsonparser/CMakeLists.txt;0;")
else()
  add_test(JSONParserTest NOT_AVAILABLE)
endif()
