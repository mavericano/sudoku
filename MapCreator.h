//---------------------------------------------------------------------------

#ifndef MapCreatorH
#define MapCreatorH
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "SudokuSolver.h"
//---------------------------------------------------------------------------
void init();
void getGrid(std::vector<std::vector<int>> &resultGrid);
enum Ret {Unique, NotUnique, NoSolution};
Ret TestUniqueness();
#endif
