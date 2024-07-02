cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(response-parser VERSION 1.0 DESCRIPTION "Parses JSON responses from Rick And Morty API.")

add_executable(response-parser
    main.cpp
)

# Add JSONC Dependency

include(FetchContent)

FetchContent_Declare(
  JSONC
  GIT_REPOSITORY git@github.com:st235/JSONC.git
  GIT_TAG "main"
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
)
FetchContent_MakeAvailable(JSONC)

target_link_libraries(response-parser jsonc)
