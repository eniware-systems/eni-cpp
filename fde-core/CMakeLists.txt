cmake_minimum_required(VERSION 3.19)

set(FDE_PACKAGE_VERSION 0.1)
include(${CMAKE_SOURCE_DIR}/cmake/fde-build.cmake)

project(fde-core VERSION ${FDE_PACKAGE_VERSION} LANGUAGES CXX)

set(TARGET_NAME Core)

add_library(${TARGET_NAME}
        fde/Engine.cpp fde/Engine.h
        fde/EngineObject.h
        fde/EngineReference.h
        fde/Node.cpp fde/Node.h
        fde/schemapush.h
        fde/Schema.cpp fde/Schema.h
        )

include(dependency-versions)
fde_set_target_defaults(
        TARGET_NAME ${TARGET_NAME}
        PREFIX fde
        PACKAGE_VERSION ${FDE_PACKAGE_VERSION}
)

target_link_libraries(${TARGET_NAME} PUBLIC Eni::Common)

# Tests
eni_add_unit_test(NAME EngineTests SOURCES tests/EngineTests.cpp LIBS ${TARGET_NAME})
