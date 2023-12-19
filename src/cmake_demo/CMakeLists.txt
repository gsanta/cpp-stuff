cmake_minimum_required(VERSION 3.16)
project(CmakeDemo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    stduuid
    GIT_REPOSITORY https://github.com/mariusbancila/stduuid.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(stduuid)

set(DEMO_PROJ "demo_proj")
file(GLOB DEMO_PROJ_SOURCES
    "main.cpp"
    "file1.cpp"
)

set(LIB1 "lib1")
file(GLOB LIB1_SOURCES
    "static_lib/calc.cpp"
)
add_library(${LIB1} ${LIB1_SOURCES})

set(LIB2 "lib2")
file(GLOB LIB2_SOURCES
    "shared_lib/shared_lib.cpp"
)
add_library(${LIB2} SHARED ${LIB2_SOURCES})

add_executable(${DEMO_PROJ} ${DEMO_PROJ_SOURCES})
target_link_libraries(${DEMO_PROJ} stduuid ${LIB1} ${LIB2})
target_include_directories(${DEMO_PROJ} PUBLIC "./include")
