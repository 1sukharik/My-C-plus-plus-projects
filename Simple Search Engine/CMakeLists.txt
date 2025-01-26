cmake_minimum_required(VERSION 3.26)
project(IndexCreator)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(Index
        index/bin/main.cpp
        index/lib/index.h
        index/lib/index.cpp
        tests/index_test.cpp

)
add_executable(Query
        query/bin/main.cpp
        query/lib/query.h
        query/lib/query.cpp
)


target_link_libraries(Index gtest gmock gtest_main gmock_main)


enable_testing()

add_executable(
        tests
        tests/index_test.cpp
)


target_link_libraries(
        tests
        gtest_main
        gmock_main
)

include(GoogleTest)
gtest_discover_tests(tests)
