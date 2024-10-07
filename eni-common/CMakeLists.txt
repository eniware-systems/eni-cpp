cmake_minimum_required(VERSION 3.27)

set(ENI_PACKAGE_VERSION 0.1)

include(eni-build)

project(eni-common VERSION ${ENI_PACKAGE_VERSION} LANGUAGES CXX)

set(TARGET_NAME Common)

if (NOT ENI_STATIC)
    add_library(${TARGET_NAME} SHARED)
else ()
    add_library(${TARGET_NAME} STATIC)
endif ()

eni_gather_sources(TARGET ${TARGET_NAME} eni)

eni_set_target_defaults(
        TARGET_NAME ${TARGET_NAME}
        PREFIX eni
        PACKAGE_VERSION ${ENI_PACKAGE_VERSION}
)

find_package(spdlog REQUIRED)
target_link_libraries(${TARGET_NAME} PUBLIC spdlog::spdlog)

find_package(fmt REQUIRED)
target_link_libraries(${TARGET_NAME} PUBLIC fmt::fmt)

# Tests
eni_add_unit_test(NAME InterceptorTests SOURCES tests/InterceptorTests.cpp LIBS ${TARGET_NAME})
# Reminder: We can skip the NAME argument if we only have one source!
eni_add_unit_test(SOURCES tests/UtilTests.cpp LIBS ${TARGET_NAME})
eni_add_unit_test(SOURCES tests/EventDispatcherTests.cpp LIBS ${TARGET_NAME})
eni_add_unit_test(SOURCES tests/StringifyTests.cpp LIBS ${TARGET_NAME})
eni_add_unit_test(SOURCES tests/TypeTraitsTests.cpp LIBS ${TARGET_NAME})

add_subdirectory(tests/embed_data_test)
