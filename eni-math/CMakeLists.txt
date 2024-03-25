cmake_minimum_required(VERSION 3.27)

set(ENI_PACKAGE_VERSION 0.1)

include(eni-build)

project(eni-math VERSION ${ENI_PACKAGE_VERSION} LANGUAGES CXX)

set(TARGET_NAME Math)

eni_gather_sources(OUT LIB_SOURCES eni)

add_library(${TARGET_NAME} ${LIB_SOURCES})

target_link_libraries(${TARGET_NAME} PUBLIC Eni::Common)

eni_set_target_defaults(
        TARGET_NAME ${TARGET_NAME}
        PREFIX eni
        PACKAGE_VERSION ${ENI_PACKAGE_VERSION}
)

# Tests
eni_add_unit_test(SOURCES tests/BoundingBoxTests.cpp LIBS ${TARGET_NAME})
eni_add_unit_test(SOURCES tests/MathTests.cpp LIBS ${TARGET_NAME})
eni_add_unit_test(SOURCES tests/QuaternionTests.cpp LIBS ${TARGET_NAME})
