enable_testing()

set(TEST_SOURCES
    SudokuSolverTest.cpp
    # Add other test files here
)

add_executable(SudokuSolverTests ${TEST_SOURCES})

# Link with gtest and SudokuSolver library
target_link_libraries(SudokuSolverTests gtest_main SudokuSolverLib)

# Add tests
include(GoogleTest)

gtest_discover_tests(SudokuSolverTests)