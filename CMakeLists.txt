cmake_minimum_required(VERSION 3.15)

project(termlink CXX)

set(MAKEFLAGS = --no-print-directory)

if(NOT SRC_DIR)
    set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
endif()

add_executable(termlink
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/main.h
    ${SRC_DIR}/GcTable.cpp
    ${SRC_DIR}/GcTerminal.cpp
    ${SRC_DIR}/GameComponents.h
    ${SRC_DIR}/game.cpp
)

if(NOT CMAKE_BUILD_TYPE MATCHES Debug)
    target_sources(termlink PRIVATE ${SRC_DIR}/intro.cpp)
endif()