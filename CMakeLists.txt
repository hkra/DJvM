cmake_minimum_required (VERSION 2.6)
project (djvm)

SET(CMAKE_CXX_FLAGS --std=c++14)

add_executable(djvm src/djvm.cpp src/util/program_options.cpp)