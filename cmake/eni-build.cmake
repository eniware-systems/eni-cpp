cmake_minimum_required(VERSION 3.27)

include(eni-util)

if (NOT DEFINED ${ENI_PACKAGE_VERSION})
    set(ENI_PACKAGE_VERSION 0.0.1)
endif ()

# Initializes common settings for building projects
macro(eni_set_target_defaults)
    set(Boost_NO_WARN_NEW_VERSIONS 1)
    set(options NO_EXPORT)
    set(oneValueArgs TARGET_NAME PACKAGE_VERSION PREFIX)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}"
            "${multiValueArgs}" ${ARGN})

    eni_string_to_camel_case("${ARG_PREFIX}" PREFIX_CC)
    string(TOUPPER "${PREFIX_CC}" PREFIX_UC)

    message(STATUS "Setting up target ${ARG_TARGET_NAME} (${ARG_PACKAGE_VERSION}) in namespace ${PREFIX_CC} using prefix ${PREFIX_UC}")

    target_compile_definitions(${ARG_TARGET_NAME} PUBLIC "${PREFIX_UC}_DEBUG")
    target_compile_definitions(${ARG_TARGET_NAME} PRIVATE "${PREFIX_UC}_SOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"")
    target_compile_definitions(${ARG_TARGET_NAME} PUBLIC "${PREFIX_UC}_VERSION=${ARG_PACKAGE_VERSION}")
    target_include_directories(${ARG_TARGET_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

    set_property(TARGET ${ARG_TARGET_NAME} PROPERTY CXX_STANDARD 23)
    set_property(TARGET ${ARG_TARGET_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
    set_property(TARGET ${ARG_TARGET_NAME} PROPERTY CXX_EXTENSIONS OFF)
    set_property(TARGET ${ARG_TARGET_NAME} PROPERTY CXX_FLAGS "-fcoroutines -Wall -Wextra")
    set_property(TARGET ${ARG_TARGET_NAME} PROPERTY CXX_FLAGS_DEBUG "-g")
    set_property(TARGET ${ARG_TARGET_NAME} PROPERTY CXX_FLAGS_RELEASE "-O0")
    set_property(TARGET ${ARG_TARGET_NAME} PROPERTY POSITION_INDEPENDENT_CODE "ON")

    get_target_property(TARGET_TYPE ${ARG_TARGET_NAME} TYPE)
    if (NOT TARGET_TYPE STREQUAL "EXECUTABLE")
        add_library(${PREFIX_CC}::${ARG_TARGET_NAME} ALIAS ${ARG_TARGET_NAME})
    endif ()

    if (NOT ${ARG_NO_EXPORT})
        # Export the targets
        export(TARGETS ${ARG_TARGET_NAME} NAMESPACE ${PREFIX_CC}:: FILE "${PREFIX_CC}${ARG_TARGET_NAME}Targets.cmake")

        # Export the package (only works if CMAKE_EXPORT_PACKAGE_REGISTRY is enabled)
        export(PACKAGE ${PREFIX_CC})

        # Create the package version config file
        include(CMakePackageConfigHelpers)
        write_basic_package_version_file(
                "${PREFIX_CC}${ARG_TARGET_NAME}ConfigVersion.cmake"
                VERSION ${${PREFIX_UC}_PACKAGE_VERSION}
                COMPATIBILITY AnyNewerVersion
        )
    endif ()
endmacro(eni_set_target_defaults)

# Add a new unit test - all credits go to CMacIonize (https://github.com/bwvdnbro/CMacIonize)
# A new target with the test sources is constructed, and a CTest test with the
# same name is created. The new test is also added to the global list of test
# contained in the check target.
#
# Params:
#   PARALLEL: Whether to apply MPI flags for parallelization
#   NAME: The name of the test
#   SOURCES: A list of source files
#   LIBS: A list of libraries to link with
#   INCLUDE_DIRS: Additional include directories for this test
#
# When compiled, the following macros will be available:
#   ENI_TEST_SOURCE_DIR: The directory of the first source file
#
macro(eni_add_unit_test)
    set(options PARALLEL)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES LIBS INCLUDE_DIRS)
    cmake_parse_arguments(TEST "${options}" "${oneValueArgs}"
            "${multiValueArgs}" ${ARGN})

    if (NOT TEST_NAME)
        list(LENGTH TEST_SOURCES len)
        if (NOT "${len}" EQUAL 1)
            message(FATAL_ERROR "No NAME was provided for unit test but the test has more than one source file")
        endif ()

        list(GET TEST_SOURCES 0 TEST_NAME)
        get_filename_component(TEST_NAME ${TEST_NAME} NAME_WE)
    endif ()

    find_package(Catch2 CONFIG)
    if (NOT Catch2_FOUND)
        message(WARNING "Could not find Catch2, unit tests for ${TEST_NAME} are disabled")
        return()
    endif ()

    message(STATUS "Generating Unit test ${TEST_NAME}")
    #add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_SOURCES})
    add_executable(${TEST_NAME} ${TEST_SOURCES})
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
            ${PROJECT_BINARY_DIR}/rundir/test)
    target_link_libraries(${TEST_NAME} PRIVATE ${TEST_LIBS})

    eni_set_target_defaults(${TEST_NAME} TARGET_NAME ${TEST_NAME} NO_EXPORT)

    target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain)
    target_include_directories(${TEST_NAME} PRIVATE ${TEST_INCLUDE_DIRS})

    list(GET TEST_SOURCES 0 ENI_TEST_SOURCE_DIR)
    get_filename_component(ENI_TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${ENI_TEST_SOURCE_DIR}" DIRECTORY)
    target_compile_definitions(${TEST_NAME} PRIVATE ENI_TEST_SOURCE_DIR="${ENI_TEST_SOURCE_DIR}")

    if (TEST_PARALLEL AND HAVE_MPI)
        set(TESTCOMMAND ${MPIEXEC})
        set(TESTARGS ${MPIEXEC_NUMPROC_FLAG} 3 ${MPIEXEC_PREFLAGS}
                "./${TEST_NAME}" ${MPIEXEC_POSTFLAGS})
        set(TESTCOMMAND ${TESTCOMMAND} ${TESTARGS})
    else (TEST_PARALLEL AND HAVE_MPI)
        set(TESTCOMMAND ${TEST_NAME})
    endif (TEST_PARALLEL AND HAVE_MPI)

    add_test(NAME ${TEST_NAME}
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/rundir/test
            COMMAND ${TESTCOMMAND})

    set(TESTNAMES ${TESTNAMES} ${TEST_NAME})
endmacro(eni_add_unit_test)
