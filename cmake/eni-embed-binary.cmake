
function(eni_embed_binary)
    set(options TARGET FILENAME OUT)

    cmake_parse_arguments(
            ARG
            ""
            "${options}"
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

    get_filename_component(VAR_NAME ${ARG_OUT} NAME)

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

    set(output_c "
#include \"${VAR_NAME}.h\"
uint8_t ${VAR_NAME}_data[] = {
    ${output_c}
};
unsigned ${VAR_NAME}_size = sizeof(${VAR_NAME}_data);
")

    string(TOUPPER "${VAR_NAME}_H" HEADER_GUARD)

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