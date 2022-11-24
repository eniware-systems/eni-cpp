cmake_minimum_required(VERSION 3.21)

# Capitalizes a string
function(eni_string_capitalize STR RESULT)
    string(SUBSTRING ${STR} 0 1 HEAD)
    string(TOUPPER ${HEAD} HEAD)
    string(SUBSTRING ${STR} 1 -1 TAIL)

    set(${RESULT} "${HEAD}${TAIL}" PARENT_SCOPE)
endfunction()

# Converts a string into CamelCase
function(eni_string_to_camel_case STR OUT)
    string(REGEX REPLACE "[-_\\w]+" ";" TMP "${STR}")
    string(REGEX REPLACE "([A-Z]+)([A-Z][a-z]+)" "\\1;\\2" TMP "${TMP}")
    string(REGEX REPLACE "([a-z]+)([A-Z])" "\\1;\\2" TMP "${TMP}")
    string(TOLOWER "${TMP}" TMP)

    foreach(COMPONENT ${TMP})
        eni_string_capitalize(${COMPONENT} COMPONENT)
        set(RESULT "${RESULT}${COMPONENT}")
    endforeach()

    set(${OUT} "${RESULT}" PARENT_SCOPE)
endfunction()