#include "../src/SudokuSolver.h"
#include "gtest/gtest.h"
#include <tuple>

class SudokuSolverTest : public ::testing::TestWithParam<
                             std::tuple<const char *, bool, const char *>> {
protected:
  SudokuSolver sudokuSolver;
};

TEST_P(SudokuSolverTest, TestCase) {
  auto [input, is_solved, output] = GetParam();
  EXPECT_EQ(sudokuSolver.solveSudoku(input), is_solved);
  EXPECT_EQ(sudokuSolver.outputSudoku(), output);
}

INSTANTIATE_TEST_CASE_P(
    EdgeCases, SudokuSolverTest,
    ::testing::Values(
        // Blank board
        std::make_tuple("000000000000000000000000000000000000000000000000000000"
                        "000000000000000000000000000",
                        false, "-1"),
        // Already complete
        std::make_tuple("689325147354817926712694385243971658978563214165248739"
                        "896432571437159862521786493",
                        true,
                        "689325147354817926712694385243971658978563214165248739"
                        "896432571437159862521786493"),
        // Incomplete starting point
        std::make_tuple("689325147354817926712694385243971658978563214165248739"
                        "8964325714371598625217",
                        false, "-1"),
        // Starting point not valid -> too big
        std::make_tuple("689325147354817926712694385243971658978563214165248739"
                        "896432571437159862521786123456789493",
                        false, "-1"),
        // Starting point not valid -> too small
        std::make_tuple("6893251473548179267126943852439716589", false, "-1"),
        // Starting point not valid -> not a number
        std::make_tuple("6893251473a4817926712694385243971658978563214165248739"
                        "8964325714371598625217",
                        false, "-1")));

INSTANTIATE_TEST_CASE_P(EasyTestCases, SudokuSolverTest,
                        ::testing::Values(std::make_tuple(
                            "08900514030081700671060438004390000097000001400000"
                            "8730096402071400159002021700490",
                            true,
                            "68932514735481792671269438524397165897856321416524"
                            "8739896432571437159862521786493")));

INSTANTIATE_TEST_CASE_P(MediumTestCases, SudokuSolverTest,
                        ::testing::Values(std::make_tuple(
                            "07130002900000615000000130000701080000008724060005"
                            "0700598002000030070006004030002",
                            true,
                            "87134562934972615825689137442791386591568724368325"
                            "4791598162437132479586764538912")));

INSTANTIATE_TEST_CASE_P(HardTestCases, SudokuSolverTest,
                        ::testing::Values(std::make_tuple(
                            "09000430030008050100001004080100693000630500700009"
                            "0005005009200004160000000000406",
                            true,
                            "19725436834268759156891374285172693492634518747389"
                            "1625685479213734162859219538476")));

INSTANTIATE_TEST_CASE_P(
    Unsolvable, SudokuSolverTest,
    ::testing::Values(
        // Unsolvable Square
        std::make_tuple("00902870080600400500300000460000000002071345000000"
                        "0002300000500900400807001250300",
                        false, "-1"),
        // Unsolvable Box
        std::make_tuple("09030000100008004600000080040506003000327560006001090"
                        "4001000000580020000200007060",
                        false, "-1"),
        // Unsolvable Column
        std::make_tuple("00004100006000002000200000032060000000005004170000000"
                        "2000000230048000000501002000",
                        false, "-1"),
        // Unsolvable Row
        std::make_tuple("900100004014030800003000090000708001800003000000000030"
                        "021000070009040500500016003",
                        false, "-1")));

bool isValidSolution(const char *output) {
  vector<vector<uint8_t>> board(9, vector<uint8_t>(9));

  for (int i = 0; i < 81; i++) {
    board[i / 9][i % 9] = output[i] - '0';
  }

  // Check rows
  for (const auto &row : board) {
    vector<bool> seen(10, false);
    for (uint8_t num : row) {
      if (num == 0 || seen[num]) {
        return false;
      }
      seen[num] = true;
    }
  }

  // Check columns
  for (int col = 0; col < 9; col++) {
    vector<bool> seen(10, false);
    for (int row = 0; row < 9; row++) {
      uint8_t num = board[row][col];
      if (num == 0 || seen[num]) {
        return false;
      }
      seen[num] = true;
    }
  }

  // Check boxes
  for (int boxRow = 0; boxRow < 9; boxRow += 3) {
    for (int boxCol = 0; boxCol < 9; boxCol += 3) {
      vector<bool> seen(10, false);
      for (int row = boxRow; row < boxRow + 3; row++) {
        for (int col = boxCol; col < boxCol + 3; col++) {
          uint8_t num = board[row][col];
          if (num == 0 || seen[num]) {
            return false;
          }
          seen[num] = true;
        }
      }
    }
  }

  return true;
}

// General check but technically an invalid sudoku if there are many solutions
TEST(SudokuSolverTest, MultipleSolutions) {
  // Arrange
  const char *input = "29574386143186590087619254338745921661238749554921673876"
                      "3524189928671354154938600";

  SudokuSolver solver;

  // Assert
  EXPECT_EQ(solver.solveSudoku(input), true);
  EXPECT_TRUE(isValidSolution(solver.outputSudoku().c_str()));
}