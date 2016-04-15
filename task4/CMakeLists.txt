cmake_minimum_required(VERSION 3.1)

set (git_cmd "cmd /c dir")
message(STATUS "git cmd: ${git_cmd}")
execute_process(COMMAND ${git_cmd}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  OUTPUT_VARIABLE git_ver)

message(STATUS "Result: ${git_ver}")

message("Ох уж эти стандарты :(")

project(format CXX)

add_subdirectory(hexfloat)
             
add_library(format STATIC format.cpp)
target_compile_features(format PRIVATE cxx_variadic_templates)
target_link_libraries(format hexfloat)

install (TARGETS format DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install (FILES format.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

add_executable(formatexe format.cpp)
target_compile_features(formatexe PRIVATE cxx_variadic_templates)
target_link_libraries(formatexe hexfloat)

install (TARGETS formatexe DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
# For local tests
# add_definitions(-DRELEASE)
