cmake_minimum_required(VERSION 3.29)
project(hxsa_x64 LANGUAGES CXX)

option(BUILD_TESTS "Build Tests" ON)

cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0091 NEW)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(assembler)
add_subdirectory(isa)
add_subdirectory(vm)

if (BUILD_TESTS)
    enable_testing()
    # add_subdirectory()
endif()