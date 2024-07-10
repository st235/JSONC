cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(JSONC VERSION 0.2 DESCRIPTION "JSONC is a lightweight implementation of JSON Data Interchange Standard for C++ programming language.")

# Library targets.

add_library(jsonc
    src/json_parser.h
    src/json_parser.cpp
    src/json_token_reader.h
    src/json_minifier.cpp
    src/json_beautifier.cpp
    src/json.cpp
)

if(MSVC)
  target_compile_options(jsonc PRIVATE /W4 /WX)
else()
  target_compile_options(jsonc PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

set_property(TARGET jsonc PROPERTY COMPILE_WARNING_AS_ERROR ON)

target_include_directories(jsonc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

if (ASSERT)
  message("Enabling assertions in the code")
  add_compile_definitions(ASSERT=${ASSERT})
endif()

# Test targets.

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(jsonc_tests
  # Utils.
  tests/integration/test_utils.h

  # Unit tests.
  #  Testing types.
  tests/unit/json_null_tests.cpp
  tests/unit/json_boolean_tests.cpp
  tests/unit/json_number_tests.cpp
  tests/unit/json_string_tests.cpp
  tests/unit/json_array_tests.cpp
  tests/unit/json_object_tests.cpp
  #  Internal types tests.
  tests/unit/json_token_reader_tests.cpp

  # Integration tests.
  tests/integration/json_dump_tests.cpp
  tests/integration/json_malformed_json_tests.cpp
  tests/integration/json_valid_json_tests.cpp
  #  Visitors.
  tests/integration/json_beautifier_tests.cpp
  tests/integration/json_minifier_tests.cpp
)

target_link_libraries(jsonc_tests jsonc)
# GMock is required to use EXPECT_THAT.
target_link_libraries(jsonc_tests GTest::gtest_main GTest::gmock_main)
target_include_directories(jsonc_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

include(GoogleTest)
gtest_discover_tests(jsonc_tests)
