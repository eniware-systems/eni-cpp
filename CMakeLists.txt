cmake_minimum_required(VERSION 3.27)

project(eni-commons)

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})
set(ENI_HOME "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "ENI_HOME")

add_subdirectory(eni-common)
add_subdirectory(eni-math)
