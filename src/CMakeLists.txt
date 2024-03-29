set(SOURCES
    SudokuSolver.cpp
    SudokuSolver.h
    sudoku_solvers/SudokuSolverAlgorithm.h
    sudoku_solvers/brute_force/BruteForceSolver.cpp
    sudoku_solvers/brute_force/BruteForceSolver.h
)

# Create a library target
add_library(SudokuSolverLib ${SOURCES})

# Create an executable target and link with the library
add_executable(SudokuSolver main.cpp)
target_link_libraries(SudokuSolver SudokuSolverLib)