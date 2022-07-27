cmake_minimum_required(VERSION 3.17)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(search_engine main.cpp ConverterJSON.cpp SearchServer.cpp InvertedIndex.cpp
                ${MY_INCLUDE_DIR}/ConverterJSON.h ${MY_INCLUDE_DIR}/SearchServer.h ${MY_INCLUDE_DIR}/InvertedIndex.h)

target_include_directories(search_engine PUBLIC ${MY_INCLUDE_DIR})