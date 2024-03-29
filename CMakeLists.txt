cmake_minimum_required(VERSION 3.16)

project(
    sudoku_solver
    VERSION 1.0.0
    DESCRIPTION "Solve 9x9 Sudoku puzzles"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download and configure gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include source and test directories
add_subdirectory(src)
add_subdirectory(test)

enable_testing()