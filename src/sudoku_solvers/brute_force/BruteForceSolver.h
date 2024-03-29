#pragma once
#include "../SudokuSolverAlgorithm.h"

using namespace std;

class BruteForceSolver : public SudokuSolverAlgorithm {
  bool addNumber(uint8_t row, uint8_t col, vector<vector<uint8_t>>* matrix, uint8_t cell_number);
  bool checkChoice(vector<vector<uint8_t>>* matrix, uint8_t row, uint8_t col, uint8_t choice);
public:
  bool solveSudoku(vector<vector<uint8_t>>* matrix) override;
};