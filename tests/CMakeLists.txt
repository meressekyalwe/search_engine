cmake_minimum_required(VERSION 3.17)

project(GoogleTest)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(../include ../src)

#set(gtest_disable_pthreads on) #needed in MinGW

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(GoogleTest  InvertedIndex_test.cpp SearchServer_test.cpp ../src/ConverterJSON.cpp ../src/InvertedIndex.cpp ../src/SearchServer.cpp)

target_link_libraries(GoogleTest PRIVATE gtest_main)

include(GoogleTest)

gtest_discover_tests(GoogleTest)

set(JSON_BuildTests OFF CACHE INTERNAL "")

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)

FetchContent_MakeAvailable(json)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)