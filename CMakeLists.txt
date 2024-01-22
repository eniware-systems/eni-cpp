cmake_minimum_required(VERSION 3.27)

project(eni-commons)

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_BINARY_DIR})

add_subdirectory(eni-common)

