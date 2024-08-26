
function(eni_embed_binary)
    cmake_parse_arguments(
            ARG
            ""
            "TARGET;FILENAME;OUT;VAR"
            ""
            ${ARGN}
    )

    eni_debug_dump_variables()

    if (NOT ARG_FILENAME)
        message(FATAL_ERROR "No FILENAME parameter specified")
    endif ()

    if (NOT ARG_OUT)
        message(FATAL_ERROR "No OUT parameter specified")
    endif ()

    if (NOT ARG_VAR)
        set(VAR_NAME ${ARG_OUT})
    else ()
        set(VAR_NAME ${ARG_VAR})
    endif ()

    string(REGEX REPLACE "[^a-zA-Z0-9]" "_" VAR_NAME "${VAR_NAME}")
    string(REGEX REPLACE "_+$" "" VAR_NAME "${VAR_NAME}")
    string(REGEX REPLACE "^_+" "" VAR_NAME "${VAR_NAME}")
    string(REGEX REPLACE "_+" "_" VAR_NAME "${VAR_NAME}")

    file(READ ${ARG_FILENAME} data HEX)
    string(REGEX MATCHALL "([A-Fa-f0-9][A-Fa-f0-9])" SEPARATED_HEX ${data})

    set(output_c "")

    set(counter 0)
    foreach (hex IN LISTS SEPARATED_HEX)
        string(APPEND output_c "0x${hex},")
        MATH(EXPR counter "${counter}+1")
        if (counter GREATER 16)
            string(APPEND output_c "\n    ")
            set(counter 0)
        endif ()
    endforeach ()

    string(REGEX REPLACE "[^a-zA-Z0-9]" "_" HEADER_GUARD "${ARG_OUT}_BINARY_DATA_INCLUDED")
    string(REGEX REPLACE "^_+" "" HEADER_GUARD "${HEADER_GUARD}")
    string(REGEX REPLACE "_+$" "" HEADER_GUARD "${HEADER_GUARD}")
    string(REGEX REPLACE "_+" "_" HEADER_GUARD "${HEADER_GUARD}")
    string(TOUPPER "${HEADER_GUARD}_H" HEADER_GUARD)

    set(output_c "
#include \"${ARG_OUT}.h\"
uint8_t ${VAR_NAME}_data[] = {
    ${output_c}
};
unsigned ${VAR_NAME}_size = sizeof(${VAR_NAME}_data);
")

    set(output_h "
#ifndef ${HEADER_GUARD}
#define ${HEADER_GUARD}
#include \"stdint.h\"
extern uint8_t ${VAR_NAME}_data[];
extern unsigned ${VAR_NAME}_size;
#endif // ${HEADER_GUARD}
    ")

    set(filename_h "${ARG_OUT}.h")
    set(filename_c "${ARG_OUT}.c")

    if (NOT IS_ABSOLUTE "${filename_h}")
        set(filename_h "${CMAKE_CURRENT_BINARY_DIR}/${filename_h}")
    endif ()

    if (NOT IS_ABSOLUTE "${filename_c}")
        set(filename_c "${CMAKE_CURRENT_BINARY_DIR}/${filename_c}")
    endif ()

    file(WRITE "${filename_c}" "${output_c}")
    file(WRITE "${filename_h}" "${output_h}")

    if (ARG_TARGET)
        target_sources(${ARG_TARGET} PRIVATE ${filename_c} ${filename_h})
    endif ()
endfunction()