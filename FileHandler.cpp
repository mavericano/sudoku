//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileHandler.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void saveGameToFile(std::vector<std::vector<Cell>> gridCells) {
    ofstream fout("savedGame.txt");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fout << gridCells[i][j].value << " " << gridCells[i][j].isRedactable << " ";
        }
        fout << "\n";
    }
}

void readSavedGame(std::vector<std::vector<Cell>> &gridCells, std::string path) {
    ifstream fin("savedGame.txt");

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num;
            fin >> num;
            bool stat;
            fin >> stat;
            gridCells[i][j].value = num;
            gridCells[i][j]. isRedactable = stat;
            //fout << gridCells[i][j].value << " " << gridCells[i][j].isRedactable << " ";
        }
        //fout << "\n";
    }
}
