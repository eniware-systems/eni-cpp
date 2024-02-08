cmake_minimum_required(VERSION 3.27)

set(ENI_PACKAGE_VERSION 0.1)

include(eni-build)

project(eni-spatial VERSION ${ENI_PACKAGE_VERSION} LANGUAGES CXX)

set(TARGET_NAME Spatial)

eni_gather_sources(OUT LIB_SOURCES eni)

add_library(${TARGET_NAME} ${LIB_SOURCES}
        eni/spatial/BoundingBox2.h)

target_link_libraries(${TARGET_NAME} PUBLIC Eni::Common)

eni_set_target_defaults(
        TARGET_NAME ${TARGET_NAME}
        PREFIX eni
        PACKAGE_VERSION ${ENI_PACKAGE_VERSION}
)

# Tests
