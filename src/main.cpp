#include "SudokuSolver.h"
#include <getopt.h>
#include <iostream>

using namespace std;

void print_help() {
  cout
      << "--input<i>:            Input the sudoku to be solved. String of "
         "numbers starting at the top left and working down to the bottom from "
         "left to right. Missing numbers should be set as 0 in the string.\n"
         "--help:                Show help\n";
}

int main(int argc, char *argv[]) {
  const char *const short_opts = "i:h";
  const option long_opts[] = {{"input", required_argument, nullptr, 'i'},
                              {"help", no_argument, nullptr, 'h'},
                              {nullptr, no_argument, nullptr, 0}};

  string sudoku_input = "";

  while (true) {
    const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
    if (-1 == opt)
      break;

    switch (opt) {
    case 'i':
      sudoku_input = string(optarg);
      break;

    case 'h': // -h or --help
    default:
      print_help();
      break;
    }
  }

  SudokuSolver sudokuSolver;

  return !sudokuSolver.solveSudoku(sudoku_input);
}
