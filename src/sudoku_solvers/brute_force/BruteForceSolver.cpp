#include "BruteForceSolver.h"
#include <cmath>

bool BruteForceSolver::solveSudoku(vector<vector<uint8_t>> *matrix) {
  return addNumber(0, 0, matrix, 0);
}

/*
 * Add a valid choice to the row/col position. Recursively call the next cell.
 *  cell_number is the current cell number (0-80), counting from left to right,
 * top to bottom.
 */
bool BruteForceSolver::addNumber(uint8_t row, uint8_t col,
                                 vector<vector<uint8_t>> *matrix,
                                 uint8_t cell_number) {
  // reach the end of the matrix
  if (cell_number == 81)
    return true;

  // can skip the cell if it's already filled
  if (matrix->at(row).at(col)) {
    cell_number++;
    uint32_t next_row = floor(cell_number / 9);
    uint32_t next_col = cell_number % 9;

    return addNumber(next_row, next_col, matrix, cell_number);
  }

  // find choice for the cell
  for (uint32_t choice = 1; choice <= 9; choice++) {
    if (!checkChoice(matrix, row, col, choice)) {
      matrix->at(row).at(col) = 0;
      continue;
    }

    matrix->at(row).at(col) = choice;

    uint32_t next_row = floor((cell_number + 1) / 9);
    uint32_t next_col = (cell_number + 1) % 9;

    if (addNumber(next_row, next_col, matrix, cell_number + 1))
      return true;
    else
      matrix->at(row).at(col) = 0;
  }

  return false;
}

/*
 * Check to see if the choice is a valid choice for the position
 */
bool BruteForceSolver::checkChoice(vector<vector<uint8_t>> *matrix, uint8_t row,
                                   uint8_t col, uint8_t choice) {
  for (uint8_t i = 0; i < 9; ++i) {
    uint8_t check_row = (row + i) % 9;
    uint8_t check_col = (col + i) % 9;

    if (matrix->at(check_row).at(col) == choice ||
        matrix->at(row).at(check_col) == choice)
      return false;

    uint8_t box_row_start = floor(row / 3) * 3;
    uint8_t box_col_start = floor(col / 3) * 3;

    uint8_t box_row = box_row_start + floor(i / 3);
    uint8_t box_col = box_col_start + i % 3;

    if (box_row == row && box_col == col)
      continue;

    if (matrix->at(box_row).at(box_col) == choice)
      return false;
  }

  return true;
}