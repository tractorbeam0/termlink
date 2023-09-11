cmake_minimum_required(VERSION 3.15)

project(termlink CXX)

set(MAKEFLAGS = --no-print-directory)

add_executable(termlink
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/main.h
    ${SRC_DIR}/termfunk.cpp
    ${SRC_DIR}/termfunk.h
    ${SRC_DIR}/intro.cpp
    ${SRC_DIR}/game.cpp
)