cmake_minimum_required(VERSION 3.1)
 
project(lazy_string CXX)
             
add_library(lazy_string STATIC lazy_string.cpp)
install (TARGETS lazy_string DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install (FILES lazy_string.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
