//---------------------------------------------------------------------------

#pragma hdrstop

#include "MapCreator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
std::vector<std::vector<int>> BASE_GRID(9, std::vector<int>(9));

//int ** grid = new int*[9];
std::vector<std::vector<int>> grid(9, std::vector<int>(9));

int init() {
	//[[((i*n + i/n + j) % (n*n) + 1) for j in range(n*n)] for i in range(n*n)]
	grid  = {
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
    BASE_GRID = {
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
	return BASE_GRID[0][0];
}

void transpond(){
	std::vector<std::vector<int>> temporaryGrid(9, std::vector<int>(9));
	temporaryGrid = grid;
	//memcpy(temporaryGrid, grid, sizeof(int) * 9 * 9);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			temporaryGrid[i][j] = grid[j][i];
        }
	}

	grid = temporaryGrid;
	//memcpy(grid, temporaryGrid, sizeof(int) * 9 * 9);
}

void swapRowsSmall() {
	srand(time(NULL));

	int areaToSwap = rand() % 3 + 1;
	int rowToSwap = (rand() % 3 + 1) + ((areaToSwap - 1) * 3);
	int swappedRow;
	do {
		swappedRow = (rand() % 3 + 1) + ((areaToSwap - 1) * 3);
	} while (swappedRow == rowToSwap);

	areaToSwap--;
	rowToSwap--;
	swappedRow--;

	std::vector<int> tmpRow(9);

	tmpRow = grid[rowToSwap];
	//memcpy(tmpRow, grid[rowToSwap], sizeof(int) * 9);
	grid[rowToSwap] = grid[swappedRow];
	//memcpy(grid[rowToSwap], grid[swappedRow], sizeof(int) * 9);
	grid[swappedRow] = tmpRow;
	//memcpy(grid[swappedRow], tmpRow, sizeof(int) * 9);
	/*ShowMessage(IntToStr(areaToSwap));
	ShowMessage(IntToStr(rowToSwap));
	ShowMessage(IntToStr(swappedRow));*/
}

void swapColumnsSmall() {
    srand(time(NULL));

	int areaToSwap = rand() % 3 + 1;
	int columnToSwap = (rand() % 3 + 1) + ((areaToSwap - 1) * 3);
	int swappedColumn;
	do {
		swappedColumn = (rand() % 3 + 1) + ((areaToSwap - 1) * 3);
	} while (swappedColumn == columnToSwap);

	areaToSwap--;
	columnToSwap--;
	swappedColumn--;

	std::vector<int> tmpColumn(9);

	for (int i = 0; i < 9; i++) {
		tmpColumn[i] = grid[i][columnToSwap];
	}
	//memcpy(tmpRow, grid[rowToSwap], sizeof(int) * 9);

	for (int i = 0; i < 9; i++) {
		grid[i][columnToSwap] = grid[i][swappedColumn];
	}
	//memcpy(grid[rowToSwap], grid[swappedRow], sizeof(int) * 9);

    for (int i = 0; i < 9; i++) {
		grid[i][swappedColumn] = tmpColumn[i];
	}
	//memcpy(grid[swappedRow], tmpRow, sizeof(int) * 9);
	/*ShowMessage(IntToStr(areaToSwap));
	ShowMessage(IntToStr(columnToSwap));
	ShowMessage(IntToStr(swappedColumn));*/
}

void swapRowsArea() {
	int areaToSwap = rand() % 3 + 1;
	int swappedArea;
    do {
		swappedArea = (rand() % 3 + 1);
	} while (swappedArea == areaToSwap);

	int ** tmp = new int*[3];

	//tmp[0] = grid[areaToSwap*3 - 3];
	//tmp[1] = grid[areaToSwap*3 - 2];
	//tmp[2] = grid[areaToSwap*3 - 1];

	grid[areaToSwap*3 - 3] = grid[swappedArea*3 - 3];
	//memcpy(grid[areaToSwap], grid[swappedArea],
}

void getGrid(std::vector<std::vector<int>> &resultGrid) {
	//swapColumnsSmall();
	resultGrid = grid;
}
