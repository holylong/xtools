cmake_minimum_required(VERSION 3.11)

project(wintools VERSION 1.0.1 LANGUAGES C CXX)

option(BUILD_TESTS "if build tests" ON)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(${ROOT_DIR}/cmd)

if(BUILD_TESTS)
add_subdirectory(${ROOT_DIR}/tests)
endif(BUILD_TESTS)
