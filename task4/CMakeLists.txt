cmake_minimum_required(VERSION 3.1)

# Project name and language
project(format CXX)

# Library declaration
add_library(format STATIC format.cpp)

# Variadic templates support
target_compile_features(format PRIVATE cxx_variadic_templates)

#install directories
install (TARGETS format DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install (FILES format.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install (FILES format.cpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

# For local tests
add_definitions(-DRELEASE)
