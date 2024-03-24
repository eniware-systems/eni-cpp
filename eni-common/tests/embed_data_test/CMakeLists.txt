cmake_minimum_required(VERSION 3.27)

include(eni-embed-binary)

project(EmbedDataTest)

eni_embed_binary(FILENAME ${CMAKE_CURRENT_LIST_DIR}/testdata.txt OUT foo)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/foo.c")
    message(FATAL_ERROR "File should have been generated at ${CMAKE_CURRENT_BINARY_DIR}/foo.c")
endif()