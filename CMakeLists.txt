cmake_minimum_required(VERSION 3.9...3.19)
project(ECE3504-COMPARC-PRO01 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# build main
add_executable(main main.cpp main.hpp)