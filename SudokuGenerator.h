//---------------------------------------------------------------------------

#ifndef SudokuGeneratorH
#define SudokuGeneratorH
//---------------------------------------------------------------------------
#endif#pragma package(smart_init)
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define UNASSIGNED 0

using namespace std;

class Sudoku {
private:
  int grid[9][9];
  int solnGrid[9][9];
  int guessNum[9];
  int gridPos[81];
  int difficultyLevel;
  bool grid_status;

public:
  Sudoku ();
  Sudoku (string, bool row_major=true);
  void createSeed();
  void printGrid();
  bool solveGrid();
  vector<vector<int>> getGrid();
  void countSoln(int &number);
  void genPuzzle();
  bool verifyGridStatus();
  void printSVG(string);
  void calculateDifficulty();
  int  branchDifficultyScore();
};
