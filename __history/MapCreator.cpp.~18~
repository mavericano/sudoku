//---------------------------------------------------------------------------

#pragma hdrstop

#include "MapCreator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
std::vector<std::vector<int>> BASE_GRID(9, std::vector<int>(9));
std::vector<std::vector<int>> grid(9, std::vector<int>(9));
std::vector<std::vector<int>> correctGrid(9, std::vector<int>(9));

int init() {
	//[[((i*n + i/n + j) % (n*n) + 1) for j in range(n*n)] for i in range(n*n)]
	srand(time(NULL));
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

	std::vector<std::vector<int>> tmp(3, std::vector<int>(9));

	tmp[0] = grid[areaToSwap*3 - 3];
	tmp[1] = grid[areaToSwap*3 - 2];
	tmp[2] = grid[areaToSwap*3 - 1];

	grid[areaToSwap*3 - 3] = grid[swappedArea*3 - 3];
	grid[areaToSwap*3 - 2] = grid[swappedArea*3 - 2];
	grid[areaToSwap*3 - 1] = grid[swappedArea*3 - 1];

	grid[swappedArea*3 - 3] = tmp[0];
	grid[swappedArea*3 - 2] = tmp[1];
	grid[swappedArea*3 - 1] = tmp[2];
	//memcpy(grid[areaToSwap], grid[swappedArea],
}

void swapColumnsArea() {
    int areaToSwap = rand() % 3 + 1;
	int swappedArea;
	do {
		swappedArea = (rand() % 3 + 1);
	} while (swappedArea == areaToSwap);

	std::vector<std::vector<int>> tmp(3, std::vector<int>(9));

	for (int i = 0; i < 9; i++) {
		tmp[0][i] = grid[i][areaToSwap*3 - 3];
		tmp[1][i] = grid[i][areaToSwap*3 - 2];
		tmp[2][i] = grid[i][areaToSwap*3 - 1];
	}

	for (int i = 0; i < 9; i++) {
		grid[i][areaToSwap*3 - 3] = grid[i][swappedArea*3 - 3];
		grid[i][areaToSwap*3 - 2] = grid[i][swappedArea*3 - 2];
		grid[i][areaToSwap*3 - 1] = grid[i][swappedArea*3 - 1];
	}

    for (int i = 0; i < 9; i++) {
		grid[i][swappedArea*3 - 3] = tmp[0][i];
		grid[i][swappedArea*3 - 2] = tmp[1][i];
		grid[i][swappedArea*3 - 1] = tmp[2][i];
	}
}

void shuffle() {
	int amountOfShuffles = rand() % 10 + 10;
	int currentShuffle;

	for (int i = 0; i < amountOfShuffles; i++) {
		currentShuffle = rand() % 5;

		switch (currentShuffle) {
			case 0:
				transpond();
				break;
			case 1:
				swapRowsSmall();
				break;
			case 2:
				swapColumnsSmall();
				break;
			case 3:
				swapRowsArea();
				break;
			case 4:
				swapColumnsArea();
				break;
		}
	}
}

void createTask(int difficulty) {
	int currentDifficulty = 81;
	int iterator = 0;
	std::vector<std::vector<bool>> flook (9, std::vector<bool>(9));

	while (iterator < 81) {
		int i = rand() % 9;
		int j = rand() % 9;

		if (!flook[i][j]) {
			iterator++;
			flook[i][j] = true;

			int tmp = grid[i][j];
			grid[i][j] = 0;
			currentDifficulty--;
        }
    }
}

Ret TestUniqueness()
{
    // Find untouched location with most information
    int xp = 0;
    int yp = 0;
    std::vector<byte> Mp;
    int cMp = 10;

    for(int y = 0; y < 9; y++)
    {
        for(int x = 0; x < 9; x++)
        {
            // Is this spot unused?
            if(grid[y][x] == 0)
            {
                // Set M of possible solutions
                std::vector<byte> M = {0,1,2,3,4,5,6,7,8,9};

                // Remove used numbers in the vertical direction
                for(int a = 0; a < 9; a++)
                    M[grid[a][x]] = 0;

                // Remove used numbers in the horizontal direction
                for(int b = 0; b < 9; b++)
                    M[grid[y][b]] = 0;

                // Remove used numbers in the sub square.
                //MASSIVE TODO
//                int	squareIndex = m_subSquare[y,x];
//                for(int c = 0; c < 9; c++)
//                {
//                    EntryPoint p = m_subIndex[squareIndex,c];
//                    M[m_sudoku[p.x,p.y]] = 0;
//                }

                int cM = 0;
                // Calculate cardinality of M
                for(int d = 1; d < 10; d++)
                    cM += M[d] == 0 ? 0 : 1;

                // Is there more information in this spot than in the best yet?
                if(cM < cMp)
                {
                    cMp = cM;
                    Mp = M;
                    xp = x;
                    yp = y;
                }
            }
        }
    }

    // Finished?
    if(cMp == 10)
        return Unique;

    // Couldn't find a solution?
    if(cMp == 0)
        return NoSolution;

    // Try elements
    int success = 0;
    for(int i = 1; i < 10; i++)
    {
        if(Mp[i] != 0)
        {
            grid[yp][xp] = Mp[i];

            switch(TestUniqueness())
            {
                case Unique:
                    success++;
                    break;

                case NotUnique:
                    return NotUnique;

                case NoSolution:
                    break;
            }

            // More than one solution found?
            if(success > 1)
                return NotUnique;
        }
    }

    // Restore to original state.
    grid[yp][xp] = 0;

    switch(success)
    {
        case 0:
            return NoSolution;

        case 1:
            return Unique;

        default:
            // Won't happen.
            return NotUnique;
    }
}

void getGrid(std::vector<std::vector<int>> &resultGrid) {
	shuffle();
	correctGrid = grid;
	resultGrid = grid;
}
