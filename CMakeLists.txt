cmake_minimum_required(VERSION 3.17)

project(search_engine)

set(CMAKE_CXX_STANDARD 14)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

add_subdirectory(tests)