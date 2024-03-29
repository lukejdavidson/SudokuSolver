#pragma once
#include "cstdint"
#include "vector"

class SudokuSolverAlgorithm {
public:
  virtual bool solveSudoku(std::vector<std::vector<uint8_t>>* matrix) = 0;
};