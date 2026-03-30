cmake_minimum_required(VERSION 3.14)
project(algo_labs C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow")


include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.5
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(googlebenchmark)


add_executable(lab3 lab3/main.c lab3/structures.c lab3/stack.c lab3/parse.c lab3/tree.c)

enable_testing()

add_executable(tests lab3/tests.cpp lab3/structures.c lab3/stack.c lab3/parse.c lab3/tree.c)

target_link_libraries(tests gtest_main gtest stdc++ benchmark::benchmark)

include(GoogleTest)
gtest_discover_tests(tests)
