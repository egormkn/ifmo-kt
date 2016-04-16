cmake_minimum_required(VERSION 2.8)

project(hexfloat CXX)

add_library(hexfloat STATIC hexfloat.cpp)
install(TARGETS hexfloat DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES hexfloat.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)