cmake_minimum_required(VERSION 3.15)

project(termlink CXX)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(MAKEFLAGS = --no-print-directory)

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 23)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

#IF (WIN32)
#  add_compile_definitions(_WIN32)
#  set(PLATFORM = "WIN32")
#ENDIF()
#IF (UNIX)
#  add_compile_definitions(linux)
#  set(PLATFORM = "LINUX")
#ENDIF()

file(GLOB_RECURSE GLOB_SRC "${SRC_DIR}/*.h" "${SRC_DIR}/*.cpp")

add_executable(termlink ${GLOB_SRC})
