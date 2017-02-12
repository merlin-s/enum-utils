cmake_minimum_required(VERSION 3.1)
project(enum-utils CXX)

add_library(enum-utils INTERFACE)
target_include_directories(enum-utils INTERFACE enum-utils)
set_property(TARGET enum-utils PROPERTY CXX_STANDARD 11)

add_executable(enum-utils-test tests/test.cpp)
target_include_directories(enum-utils-test PUBLIC "${BOOST_ROOT}")
target_link_libraries(enum-utils-test PUBLIC enum-utils)

