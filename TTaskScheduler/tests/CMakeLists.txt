include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
        sheduler_tests.cpp
        sheduler_tests
)

target_link_libraries(
        sheduler_tests
        sheduler

        GTest::gtest_main
)

target_include_directories(sheduler_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(sheduler_tests)
