//---------------------------------------------------------------------------

#ifndef FileHandlerH
#define FileHandlerH
//---------------------------------------------------------------------------
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include "Cell.h"

void saveGameToFile(std::vector<std::vector<Cell>> gridCells, std::string path);
void readSavedGame(std::vector<std::vector<Cell>> &gridCells, std::string path);
