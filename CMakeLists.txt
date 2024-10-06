cmake_minimum_required(VERSION 3.8)
project(net)
add_compile_options(-std=c99 -g -Wall -Wextra -pedantic)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SRC_DIR "${CMAKE_BINARY_DIR}/src/")
set(INCLUDE_DIRS "${CMAKE_BINARY_DIR}/include/")
set(LIB_DIRS "${CMAKE_BINARY_DIR}/lib/")

add_library(net ${SRC_DIR}/net.c)

target_include_directories(net PUBLIC ${INCLUDE_DIRS})

target_link_libraries(net PUBLIC ${LIB_DIRS}/clog.o)
