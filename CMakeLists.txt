cmake_minimum_required(VERSION 3.1)
project(Bezier)
set(CMAKE_CXX_STANDARD 11)

option(BEZIER_TESTS "Build test suite" ON)

add_library(bezier INTERFACE)
target_include_directories(bezier INTERFACE include)

if (BEZIER_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
