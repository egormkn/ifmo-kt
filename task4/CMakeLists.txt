cmake_minimum_required(VERSION 3.0) #Chosen by a fair dice roll (c)

add_library(format STATIC format.cpp)
install (TARGETS format DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install (FILES format.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install (FILES format.cpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
