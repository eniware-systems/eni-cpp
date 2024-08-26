cmake_minimum_required(VERSION 3.27)

# Capitalizes a string
#
# Usage: eni_string_capitalize("my-string" MyVar)
function(eni_string_capitalize STR RESULT)
    string(SUBSTRING ${STR} 0 1 HEAD)
    string(TOUPPER ${HEAD} HEAD)
    string(SUBSTRING ${STR} 1 -1 TAIL)

    set(${RESULT} "${HEAD}${TAIL}" PARENT_SCOPE)
endfunction()

# Converts a string into CamelCase
#
# Usage: eni_string_to_camel_case("my-string" MyVar)
function(eni_string_to_camel_case STR OUT)
    string(REGEX REPLACE "[-_\\w]+" ";" TMP "${STR}")
    string(REGEX REPLACE "([A-Z]+)([A-Z][a-z]+)" "\\1;\\2" TMP "${TMP}")
    string(REGEX REPLACE "([a-z]+)([A-Z])" "\\1;\\2" TMP "${TMP}")
    string(TOLOWER "${TMP}" TMP)

    foreach (COMPONENT ${TMP})
        eni_string_capitalize(${COMPONENT} COMPONENT)
        set(RESULT "${RESULT}${COMPONENT}")
    endforeach ()

    set(${OUT} "${RESULT}" PARENT_SCOPE)
endfunction()

# Gathers all source files a the given directory.
#
# Parameters:
#   OUT: the name of the list variable in which the results should be stored
#   QUIET: boolean flag indicating whether to output information to the log
#
# Exmaple Usage:
#
# eni_gather_sources(OUT MY_SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/src
# )
function(eni_gather_sources)
    cmake_parse_arguments(
            ARG
            "QUIET"
            "OUT;OUT_MODULES;OUT_PRIVATE;OUT_PUBLIC;TARGET;PRIVATE_GLOB;PUBLIC_GLOB"
            ""
            ${ARGN}
    )

    if (NOT ARG_OUT)
        # set default output variable
        SET(ARG_OUT SOURCES)
    endif ()

    set(out ${ARG_OUT})
    set(out_private ${ARG_OUT_PRIVATE})
    set(out_public ${ARG_OUT_PUBLIC})

    if (NOT ARG_OUT_MODULES)
        # set default modules output variable
        SET(ARG_OUT_MODULES MODULES)
    endif ()

    set(out_modules ${ARG_OUT_MODULES})

    if (NOT ARG_PRIVATE_GLOB)
        # set default private glob patterns
        SET(ARG_PRIVATE_GLOB
                "*.c"
                "*.cpp"
                "*.cxx")
    endif ()

    if (NOT ARG_PUBLIC_GLOB)
        # set default private glob patterns
        SET(ARG_PUBLIC_GLOB
                "*.h"
                "*.hpp"
                "*.hxx")
    endif ()
    set(glob_private ${ARG_PRIVATE_GLOB})
    set(glob_public ${ARG_PUBLIC_GLOB})

    set(target ${ARG_TARGET})
    set(dirs ${ARG_UNPARSED_ARGUMENTS})

    # Sources
    set(results)
    foreach (dir IN LISTS dirs)
        set(glob_patterns)
        foreach(pattern IN LISTS glob_public)
            list(APPEND glob_patterns "${dir}/**/${pattern}")
            list(APPEND glob_patterns "${dir}/${pattern}")
        endforeach()

        file(GLOB_RECURSE dir_srcs CONFIGURE_DEPENDS ${glob_patterns})

        foreach (result IN LISTS dir_srcs)
            list(APPEND results_public ${result})
        endforeach ()

        set(glob_patterns)
        foreach(pattern IN LISTS glob_private)
            list(APPEND glob_patterns "${dir}/**/${pattern}")
            list(APPEND glob_patterns "${dir}/${pattern}")
        endforeach()

        file(GLOB_RECURSE dir_srcs CONFIGURE_DEPENDS ${glob_patterns})

        foreach (result IN LISTS dir_srcs)
            list(APPEND results_private ${result})
        endforeach ()
    endforeach ()

    set(tmp ${${out}})
    list(APPEND tmp ${results_private} ${results_public})

    if (NOT target)
        set(${out} "${tmp}" PARENT_SCOPE)
    endif ()

    set(tmp ${${out}})
    list(APPEND tmp ${results_private} ${results_public})

    if (NOT target)
        set(${out} "${tmp}" PARENT_SCOPE)
    endif ()

    if(out_public)
        set(tmp ${${out_public}})
        list(APPEND tmp ${results_public})

        if (NOT target)
            set(${out_public} "${tmp}" PARENT_SCOPE)
        endif ()
    endif()

    if(out_private)
        set(tmp ${${out_private}})
        list(APPEND tmp ${results_private})

        if (NOT target)
            set(${out_private} "${tmp}" PARENT_SCOPE)
        endif ()
    endif()

    # Modules
    set(module_extensions "ixx" , "cppm" , "mxx" , "ccm" , "cxxm")
    foreach (dir IN LISTS dirs)
        set(glob_patterns "")
        foreach (ext IN LISTS module_extensions)
            list(APPEND glob_patterns "${dir}/*.${ext}")
            list(APPEND glob_patterns "${dir}/**/*.${ext}")
        endforeach ()
        file(GLOB_RECURSE dir_srcs CONFIGURE_DEPENDS ${glob_patterns})

        foreach (result IN LISTS dir_srcs)
            list(APPEND results_modules ${result})
        endforeach ()
    endforeach ()

    set(tmp ${${out_modules}})
    list(APPEND tmp ${results_modules})

    if (NOT target)
        set(${out_modules} "${tmp}" PARENT_SCOPE)
    endif ()

    if (target)
        foreach (result IN LISTS results_public)
            file(RELATIVE_PATH result_rel "${CMAKE_CURRENT_SOURCE_DIR}" ${result})
            list(APPEND sources_public "${result_rel}")
        endforeach ()

        target_sources(${target} PUBLIC ${sources_public})

        foreach (result IN LISTS results_private)
            file(RELATIVE_PATH result_rel "${CMAKE_CURRENT_SOURCE_DIR}" ${result})
            list(APPEND sources_private "${result_rel}")
        endforeach ()

        target_sources(${target} PRIVATE ${sources_private})

        if (results_modules)
            foreach (result IN LISTS results_modules)
                file(RELATIVE_PATH result_rel "${CMAKE_CURRENT_SOURCE_DIR}" ${result})
                list(APPEND all_modules "${result_rel}")
            endforeach ()

            target_sources(${target} PUBLIC FILE_SET gathered_modules TYPE CXX_MODULES FILES ${all_modules})
        endif ()
    endif ()

    if (NOT target)
        if (NOT ARG_QUIET)
            set(message "Autogenerated source list from file system. If you don't like this behaviour you can use this instead:\n")

            if(out_public AND results_public)
                set(message "${message}\nlist(APPEND ${out_public}\n")
                foreach (result IN LISTS results_public)
                    file(RELATIVE_PATH result_rel "${CMAKE_CURRENT_SOURCE_DIR}" ${result})
                    set(message "${message}\t${result_rel}\n")
                endforeach ()
                set(message "${message})")
            endif()

            if(out_private AND results_private)
                set(message "${message}\nlist(APPEND ${out_private}\n")
                foreach (result IN LISTS results_private)
                    file(RELATIVE_PATH result_rel "${CMAKE_CURRENT_SOURCE_DIR}" ${result})
                    set(message "${message}\t${result_rel}\n")
                endforeach ()
                set(message "${message})")
            endif()

            if(NOT out_private AND NOT out_public)
                set(all_results ${results_private} ${results_public})
                set(message "${message}\nlist(APPEND ${out}\n")
                foreach (result IN LISTS all_results)
                    file(RELATIVE_PATH result_rel "${CMAKE_CURRENT_SOURCE_DIR}" ${result})
                    set(message "${message}\t${result_rel}\n")
                endforeach ()
                set(message "${message})")
            endif()

            if (results_modules)
                set(message "${message}\n\nlist(APPEND ${out_modules}\n")
                set(result_rel "")
                foreach (result IN LISTS results_modules)
                    file(RELATIVE_PATH result_rel "${CMAKE_CURRENT_SOURCE_DIR}" ${result})
                    set(message "${message}\t${result_rel}\n")
                endforeach ()
                set(message "${message})")
            endif ()

            message(STATUS "${message}")
        endif ()
    else ()
        if (NOT ARG_QUIET)
            set(message "Autogenerated source list from file system. If you don't like this behaviour you can use this instead:\n")

            if(results_public)
                set(message "${message}\ntarget_sources(${target} PUBLIC\n")
                foreach (result IN LISTS results_public)
                    file(RELATIVE_PATH result_rel "${CMAKE_CURRENT_SOURCE_DIR}" ${result})
                    set(message "${message}\t${result_rel}\n")
                endforeach ()
                set(message "${message})")
            endif ()

            if(results_private)
                set(message "${message}\ntarget_sources(${target} PRIVATE\n")
                foreach (result IN LISTS results_private)
                    file(RELATIVE_PATH result_rel "${CMAKE_CURRENT_SOURCE_DIR}" ${result})
                    set(message "${message}\t${result_rel}\n")
                endforeach ()
                set(message "${message})")
            endif ()

            if (results_modules)
                set(message "${message}\n\ntarget_sources(${target} PUBLIC\n\tFILE_SET gathered_modules TYPE CXX_MODULES FILES")
                set(result_rel "")
                foreach (result IN LISTS results_modules)
                    file(RELATIVE_PATH result_rel "${CMAKE_CURRENT_SOURCE_DIR}" ${result})
                    set(message "${message}\t${result_rel}\n")
                endforeach ()
                set(message "${message})")
            endif ()

            message(STATUS "${message}")
        endif ()
    endif ()
endfunction()

# Dumps all available targets found in the current source directory
function(eni_debug_dump_targets)
    message(STATUS "Available targets: ${targets}")
    set(targets)
    eni_debug_get_targets(OUT targets)
    foreach (_target ${targets})
        message(STATUS "- ${_target}")
    endforeach ()
endfunction()

# Recursively gets all available targets found in the current source directory
# or any other directory when specified
macro(eni_debug_get_targets)
    set(options OUT DIR)

    cmake_parse_arguments(
            ARG
            ""
            "${options}"
            ""
            ${ARGN}
    )

    if (NOT ARG_OUT)
        # set default output variable
        SET(ARG_OUT TARGETS)
    endif ()

    if (NOT ARG_DIR)
        set(ARG_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    endif ()

    get_property(subdirectories DIRECTORY ${ARG_DIR} PROPERTY SUBDIRECTORIES)

    foreach (subdir ${subdirectories})
        eni_debug_get_targets(OUT ${ARG_OUT} DIR ${ARG_DIR})
    endforeach ()

    get_property(current_targets DIRECTORY ${ARG_DIR} PROPERTY BUILDSYSTEM_TARGETS)

    set(${ARG_OUT} "${ARG_OUT} ${current_targets}")
endmacro()

# Dumps all available variables found in the current build system
function(eni_debug_dump_variables)
    message(STATUS "Available variables: ${targets}")
    get_cmake_property(_variableNames VARIABLES)
    list(SORT _variableNames)
    foreach (_variableName ${_variableNames})
        if (ARGV0)
            unset(MATCHED)
            string(REGEX MATCH ${ARGV0} MATCHED ${_variableName})
            if (NOT MATCHED)
                continue()
            endif ()
        endif ()
        message(STATUS "- ${_variableName}=${${_variableName}}")
    endforeach ()
endfunction()

# Dumps a bunch of useful information about the current build environment
function(eni_debug_dump)
    eni_debug_dump_targets()
    eni_debug_dump_variables()
endfunction()
