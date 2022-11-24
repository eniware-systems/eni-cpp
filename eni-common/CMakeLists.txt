cmake_minimum_required(VERSION 3.19)

set(ENI_PACKAGE_VERSION 0.1)

include(${CMAKE_SOURCE_DIR}/cmake/eni-build.cmake)

project(eni-common VERSION ${ENI_PACKAGE_VERSION} LANGUAGES CXX)

set(TARGET_NAME Common)

add_library(${TARGET_NAME}
        eni/types.h
        eni/debug.cpp eni/debug.h
        eni/logging.cpp eni/logging.h
        eni/strings.cpp eni/strings.h
        eni/util.cpp eni/util.h

        eni/Exception.cpp eni/Exception.h
        eni/ManagedObject.h
        eni/Interceptor.h
        eni/Varying.cpp eni/Varying.cpp)

include(dependency-versions)
eni_set_target_defaults(
        TARGET_NAME ${TARGET_NAME}
        PREFIX eni
        PACKAGE_VERSION ${ENI_PACKAGE_VERSION}
        CONAN_REQUIRES
        spdlog/${ENI_SPDLOG_VERSION}
        boost/${ENI_BOOST_VERSION}
)

find_package(spdlog REQUIRED)
target_link_libraries(${TARGET_NAME} PUBLIC spdlog::spdlog)

find_package(Boost REQUIRED)
target_link_libraries(${TARGET_NAME} PUBLIC Boost::boost)

# Tests
eni_add_unit_test(NAME InterceptorTests SOURCES tests/InterceptorTests.cpp LIBS ${TARGET_NAME})
eni_add_unit_test(NAME UtilTests SOURCES tests/UtilTests.cpp LIBS ${TARGET_NAME})
