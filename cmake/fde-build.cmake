cmake_minimum_required(VERSION 3.21)

# Initializes common settings for building FDE projects
include(${CMAKE_SOURCE_DIR}/cmake/eni-build.cmake)

if(NOT DEFINED ${FDE_PACKAGE_VERSION})
    set(FDE_PACKAGE_VERSION 0.0.1)
endif()

macro(fde_set_target_defaults)
    eni_set_target_defaults(${ARGN} PACKAGE_VERSION ${FDE_PACKAGE_VERSION} PREFIX fde)
endmacro(fde_set_target_defaults)