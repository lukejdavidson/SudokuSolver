#include "SudokuSolver.h"
#include <cmath>
#include <iostream>
#include <sys/types.h>

bool SudokuSolver::parseInput(const string &sudokuString) {
  int total_elements = SIZE * SIZE;
  bool non_zero_present = false;

  if (sudokuString.size() != total_elements)
    return false;

  uint8_t row = 0;
  uint8_t col = 0;

  for (uint8_t i = 0; i < total_elements; ++i) {
    row = i / SIZE;
    col = i % SIZE;

    uint8_t val = sudokuString[i] - '0';

    if (val < 0 || val > SIZE)
        return false;

    if (!non_zero_present && val)
      non_zero_present = true;

    m_matrix.at(row).at(col) = val;
  }

  return non_zero_present;
}

bool SudokuSolver::solveSudoku(const string &sudokuString) {
  m_solved = false;

  if (!parseInput(sudokuString))
    return m_solved;

  cout << "Solving Sudoku:" << endl;
  printSudoku();

  m_solved = m_algorithm->solveSudoku(&m_matrix);

  if (m_solved) {
    cout << "Solved Sudoku:" << endl;
    printSudoku();
  } else {
    cout << "Unable to solve Sudoku" << endl;
  }

  return m_solved;
}

void SudokuSolver::printSudoku() {
  cout << TOP_CUBE_DIVIDER << endl;

  int sqrt_size = sqrt(SIZE);

  for (uint8_t row = 0; row < SIZE; ++row) {
    if (row > 0) {
      if (row % sqrt_size == 0)
        cout << MIDDLE_DIVIDER << endl;
      else
        cout << MID_CUBE_DIVIDER << endl;
    }

    cout << COL_DIVIDER;

    for (uint8_t col = 0; col < SIZE; ++col) {
      if (col > 0) {
        if (col % sqrt_size == 0)
          cout << COL_DIVIDER;
        else
          cout << "│";
      }

      cout << " " << (int)m_matrix[row][col] << " ";
    }

    cout << COL_DIVIDER << endl;
  }

  cout << BOT_CUBE_DIVIDER << endl;
}

string SudokuSolver::outputSudoku() {
  string output;

  if (!m_solved)
    return "-1";
  
  for (uint8_t row = 0; row < SIZE; ++row) {
    for (uint8_t col = 0; col < SIZE; ++col) {
      output += to_string(m_matrix[row][col]);
    }
  }

  return output;
}