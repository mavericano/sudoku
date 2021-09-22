//---------------------------------------------------------------------------

#pragma hdrstop

#include "MapCreator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

const int BASE_GRID[9][9] = {
	{1, 2, 3, 4, 5, 6, 7, 8, 9},
	{4, 5, 6, 7, 8, 9, 1, 2, 3},
	{7, 8, 9, 1, 2, 3, 4, 5, 6},
	{2, 3, 4, 5, 6, 7, 8, 9, 1},
	{5, 6, 7, 8, 9, 1, 2, 3, 4},
	{8, 9, 1, 2, 3, 4, 5, 6, 7},
	{3, 4, 5, 6, 7, 8, 9, 1, 2},
	{6 ,7 ,8, 9, 1, 2, 3, 4, 5},
	{9, 1, 2, 3, 4, 5, 6, 7, 8}
};

int grid[9][9] = {
	{1, 2, 3, 4, 5, 6, 7, 8, 9},
	{4, 5, 6, 7, 8, 9, 1, 2, 3},
	{7, 8, 9, 1, 2, 3, 4, 5, 6},
	{2, 3, 4, 5, 6, 7, 8, 9, 1},
	{5, 6, 7, 8, 9, 1, 2, 3, 4},
	{8, 9, 1, 2, 3, 4, 5, 6, 7},
	{3, 4, 5, 6, 7, 8, 9, 1, 2},
	{6 ,7 ,8, 9, 1, 2, 3, 4, 5},
	{9, 1, 2, 3, 4, 5, 6, 7, 8}
};

int returnHello() {
	//[[((i*n + i/n + j) % (n*n) + 1) for j in range(n*n)] for i in range(n*n)]
	return BASE_GRID[0][0];
}

void transpond(){
	int temporaryGrid[9][9];
	memcpy(temporaryGrid, grid, sizeof(int) * 9 * 9);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			temporaryGrid[i][j] = grid[j][i];
        }
	}

	memcpy(grid, temporaryGrid, sizeof(int) * 9 * 9);
}

void getGrid(int (&resultGrid)[9][9]) {
	memcpy(resultGrid, grid, sizeof(int) * 9 * 9);
}
