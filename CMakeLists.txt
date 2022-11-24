cmake_minimum_required(VERSION 3.19)

include(cmake/fde-build.cmake)

project(fde VERSION ${FDE_PACKAGE_VERSION} LANGUAGES CXX)

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_BINARY_DIR})

add_subdirectory(eni-common)
add_subdirectory(fde-core)
