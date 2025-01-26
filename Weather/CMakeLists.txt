cmake_minimum_required(VERSION 3.11)
project(labwork7_1sukharik)

set(CMAKE_CXX_STANDARD 20)

add_executable(labwork7_1sukharik
        main.cpp
        pictures.h
        test.cpp
        database.cpp
        interface.cpp
        database.h
        interface.h
)


include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 67e2a4d2a76ed520e352f10e651a6f98e220dbd7)
FetchContent_MakeAvailable(cpr)
target_link_libraries(labwork7_1sukharik PRIVATE cpr::cpr)


FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
target_link_libraries(labwork7_1sukharik PRIVATE nlohmann_json::nlohmann_json)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG 889c44366a0cf7c79f41ea494190954bff5febe9 # Important: Specify a version or a commit hash here.
)
FetchContent_MakeAvailable(ftxui)

project(labwork7_1sukharik LANGUAGES CXX VERSION 1.0.0)
#add_executable(labwork7_1sukharik src/main.cpp)
target_link_libraries(labwork7_1sukharik
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
)
