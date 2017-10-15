cmake_minimum_required(VERSION 3.7)
project(memcpy)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall -Werror=unused-parameter")
set(CMAKE_C_FLAGS "-Wall -Werror=unused-parameter")


set(SOURCE_FILES B.cpp)
add_executable(memcpy ${SOURCE_FILES})