cmake_minimum_required(VERSION 3.15)

project(termlink CXX)

set(MAKEFLAGS = --no-print-directory)

if(NOT SRC_DIR)
    set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
endif()

add_compile_options(-Wall -Wextra -Wpedantic -std=c++2a)

file(GLOB_RECURSE GLOB_SRC "${SRC_DIR}/*.h" "${SRC_DIR}/*.cpp")

add_executable(termlink ${GLOB_SRC})