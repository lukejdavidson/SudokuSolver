#pragma once
#include "sudoku_solvers/SudokuSolverAlgorithm.h"
#include "sudoku_solvers/brute_force/BruteForceSolver.h"
#include <memory>
#include <string>
#include <vector>

using namespace std;

static const char *TOP_CUBE_DIVIDER = "╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗";
static const char *MID_CUBE_DIVIDER = "╟───┼───┼───╫───┼───┼───╫───┼───┼───╢";
static const char *BOT_CUBE_DIVIDER = "╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝";
static const char *MIDDLE_DIVIDER = "╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣";
static const char *COL_DIVIDER = "║";
static const int SIZE = 9;

class SudokuSolver {
  vector<vector<uint8_t>> m_matrix = {SIZE, vector<uint8_t>(SIZE)};
  unique_ptr<SudokuSolverAlgorithm> m_algorithm;
  bool m_solved;

  bool parseInput(const string &sudokuString);

public:
  bool solveSudoku(const string &sudokuString);
  void printSudoku();
  string outputSudoku();
  SudokuSolver() : m_algorithm(make_unique<BruteForceSolver>()) {}
};
