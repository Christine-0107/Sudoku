cmake_minimum_required(VERSION 3.19)
project(Sudoku)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib)
include_directories(googletest/include googletest)

include_directories(.)

add_executable(Sudoku
        main.cpp
        Sudoku.cpp
        Sudoku.h instructions.h instructions.cpp)

add_executable(unitTest
        unitTest.cpp
        Sudoku.cpp
        Sudoku.h instructions.h instructions.cpp)
target_link_libraries(unitTest gtest gtest_main)

