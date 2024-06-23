cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(JSONC VERSION 0.1 DESCRIPTION "Lightweight JSON implementation in C++")

# Library targets

add_library(jsonc
    src/json_object.cpp
    src/json_parser.h
    src/json_parser.cpp
    src/json_token_reader.h
    src/json_null.cpp
    src/json_minifier.cpp
    src/json_beautifier.cpp
    src/json.cpp
)

target_include_directories(jsonc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

# Test targets
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(jsonc_tests
  tests/json_token_reader_tests.cpp
  tests/json_array_tests.cpp
  tests/json_boolean_tests.cpp
  tests/json_object_tests.cpp
  tests/json_parser_malformed_json_tests.cpp
  tests/json_valid_json_tests.cpp
  tests/json_beautifier_tests.cpp
)

target_link_libraries(jsonc_tests jsonc)
target_link_libraries(jsonc_tests GTest::gtest_main)
target_include_directories(jsonc_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

include(GoogleTest)
gtest_discover_tests(jsonc_tests)
