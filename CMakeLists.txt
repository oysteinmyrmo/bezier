cmake_minimum_required(VERSION 3.1)
project(Bezier)
set(CMAKE_CXX_STANDARD 11)

option(BEZIER_TESTS "Build test suite" ON)

if (BEZIER_TESTS)
    set(BEZIER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    enable_testing()
    add_subdirectory(tests)
endif()
