//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Sudoku.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::fillGrid(){
	std::vector<std::vector<int>> tmp(9, std::vector<int>(9));
    srand(time(NULL));
    Sudoku *sudoku = new Sudoku();
    //int t = 0;
    //do {
    sudoku->createSeed();
    sudoku->genPuzzle();
    sudoku->calculateDifficulty();
    //t++;
    //} while (t < 400);
    //ShowMessage(IntToStr(sudoku->getDifficultyLevel()));
	tmp = sudoku->getGrid();

    Cell *tmpCell;
    std::vector<Cell> tmpV;
    for (int i = 0; i < 9; i++) {
        tmpV = std::vector<Cell>();
        gridCells.push_back(tmpV);
        for (int j = 0; j < 9; j++) {
            tmpCell = new Cell(tmp[i][j]);
            if (tmpCell->value == 0) {
                tmpCell->isRedactable = true;
            }
            gridCells[i].push_back(*tmpCell);
        }
    }
}
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    //init();
	StringGrid1->DefaultDrawing = false;
	StringGrid1->DoubleBuffered = true;
	StringGrid1->GridLineWidth = 0;
	fillGrid();
    fillFromCells();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
    validateGrid();
	//Для удобства
	TCanvas *a = this->StringGrid1->Canvas;
	//Далле необходимо установить стандартные цвета, те что у тебя будут, если условие не выполняется
	//цвет как у тебя стоял если бы значение ячейки было бы равно нулю.
	a->Brush->Color = clWhite;
	//теперь, у нас ячейки бывают трех видов
	//1. Фиксированная - это когда стоит свойство fixed gdFixed
	//2. Выделенная - когда выделяешь gdSelected
	//3. и "Сфокусированная" - это на которой у тебя стоит курсор gdFocused
	//за это состояние отвечает переменная State
	//теперь ставим цвет для фиксированной ячейки
	if (State.Contains(gdFixed))
       a->Brush->Color = clMoneyGreen;
	//Так как у нас простое условие, т.е. либо больше нуля, либо меньше тогда будет так
	//У меня .ToInt() стоит, ты можешь твой тип поставить например ToDouble.
	try {
		if (!gridCells[ARow][ACol].isRedactable)
        //(this->StringGrid1->Cells[ACol][ARow].ToInt()>0))
            a->Brush->Color = (TColor) RGB(205, 197, 194);
        else
		//if ((!State.Contains(gdFixed))&&(this->StringGrid1->Cells[ACol][ARow].ToInt()<0))
            a->Brush->Color = clWhite;
        if (gridCells[ARow][ACol].isDupe) {
           a->Brush->Color = clRed;
           //ShowMessage(IntToStr(ACol) + " " + IntToStr(ARow) + " isDupe(");
        }
	} catch(...) {
		//try Нужен для того что бы если вдруг в твоей яцейки текст окажется, тогда он ее красить не будет
	}
    //тут дополнил еще что бы выделение работало
	//будет ячейку рамной обводить
    if (State.Contains(gdSelected)) {
       a->Brush->Color = (TColor) RGB(154, 206, 235);
       //a->Pen->Color = clBlue;
       //a->Rectangle(Rect);
	}
	//Все, мы установили устовия расскраски, теперь закрациваем
	a->FillRect(Rect);
	//Далее, так как DefaultDrawing = False; необходимо еще и текст напечатать.
	//можно стандартным TextRect
	//a->TextRect(Rect,Rect.left,Rect.top,this->StringGrid1->Cells[ACol][ARow]);
	//но мне нравится больше DrawText - описание есть в справке, в нем расположенние текста можно устанавливать и многое другое.
	//TRect - делает смещение.
	TRect r = Rect;
	r.left += 2;
	r.top += 2;
	a->Pen->Color = clBlack;
	a->Rectangle(Rect.left,Rect.top,Rect.right,Rect.bottom);
    a->Font->Size = 16;
	DrawText(a->Handle, this->StringGrid1->Cells[ACol][ARow].t_str(), -1, (TRect*)&r, DT_CENTER);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1SetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value)
{
//    if (!gridCells[ARow][ACol].isRedactable) {
//       //ShowMessage("nope");
//       StringGrid1->Cells[ACol][ARow] = IntToStr(gridCells[ARow][ACol].value);
//       return;
//    }
    if (Value != "") {
        const auto r = std::regex(R"([1-9]{1})");
        AnsiString tmp = Value;
        StringGrid1->Cells[ACol][ARow] = std::regex_match(tmp.c_str(), r) ? Value : "";
        gridCells[ARow][ACol].value = std::regex_match(tmp.c_str(), r) ? StrToInt(Value) : 0;
        //ShowMessage(StringGrid1->Cells[ACol][ARow]);
        //StringGrid1->Cells[0][0] = "hi";
    } else {
        gridCells[ARow][ACol].value = 0;
    }
}
void __fastcall TForm1::validateGrid() {
     //ShowMessage(StringGrid1->Cells[ACol][ARow]);
     //int value = StrToInt(StringGrid1->Cells[ACol][ARow]);
//     for (int i = 0; i < 8; i++) {
//         for (int j = 0; j < 8; j++) {
//             Cell currentCell = gridCells[i][j];
//             int value = currentCell.value;
//
//         }
//     }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            gridCells[i][j].isDupe = false;
        }
    }

    for (int col_num = 0; col_num < 9; col_num++) {
        bool nums[10]={false};
        bool toDupe[10]={false};

        for (int cell_num=0; cell_num<9; ++cell_num) {
            int curr_num = gridCells[cell_num][col_num].value;
            if(curr_num!=0 && nums[curr_num]==true) {
                toDupe[curr_num] = true;
                //gridCells[((int)(block_num/3))*3 + (cell_num/3)][((int)(block_num%3))*3 + (cell_num%3)].isDupe = true;
                //grid_status=false;
                //return;
            }
            nums[curr_num] = true;
        }
        for (int cell_num=0; cell_num<9; ++cell_num) {
            int curr_num = gridCells[cell_num][col_num].value;
            if (toDupe[curr_num]) {
                gridCells[cell_num][col_num].isDupe = true;
            }
        }
    }

    for (int row_num = 0; row_num < 9; row_num++) {
        bool nums[10]={false};
        bool toDupe[10]={false};

        for (int cell_num=0; cell_num<9; ++cell_num) {
            int curr_num = gridCells[row_num][cell_num].value;
            if(curr_num!=0 && nums[curr_num]==true) {
                toDupe[curr_num] = true;
                //gridCells[((int)(block_num/3))*3 + (cell_num/3)][((int)(block_num%3))*3 + (cell_num%3)].isDupe = true;
                //grid_status=false;
                //return;
            }
            nums[curr_num] = true;
        }
        for (int cell_num=0; cell_num<9; ++cell_num) {
            int curr_num = gridCells[row_num][cell_num].value;
            if (toDupe[curr_num]) {
                gridCells[row_num][cell_num].isDupe = true;
            }
        }
    }

    for (int block_num=0; block_num<9; ++block_num) {
        bool nums[10]={false};
        bool toDupe[10]={false};

        for (int cell_num=0; cell_num<9; ++cell_num) {
            int curr_num = gridCells[((int)(block_num/3))*3 + (cell_num/3)][((int)(block_num%3))*3 + (cell_num%3)].value;
            if(curr_num!=0 && nums[curr_num]==true) {
                toDupe[curr_num] = true;
                //gridCells[((int)(block_num/3))*3 + (cell_num/3)][((int)(block_num%3))*3 + (cell_num%3)].isDupe = true;
                //grid_status=false;
                //return;
            }
            nums[curr_num] = true;
        }
        for (int cell_num=0; cell_num<9; ++cell_num) {
            int curr_num = gridCells[((int)(block_num/3))*3 + (cell_num/3)][((int)(block_num%3))*3 + (cell_num%3)].value;
            if (toDupe[curr_num]) {
                gridCells[((int)(block_num/3))*3 + (cell_num/3)][((int)(block_num%3))*3 + (cell_num%3)].isDupe = true;
            }
        }
    }
//     for (int i = 0; i < 9 && !gridCells[ARow][ACol].isDupe; i++) {
//
//     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
    //StringGrid1SetEditText(Sender, ACol, ARow, StringGrid1->Cells[ACol][ARow]);
    CanSelect = gridCells[ARow][ACol].isRedactable;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
     if (SaveDialog1->Execute()) {
         AnsiString ans = SaveDialog1->FileName;
         saveGameToFile(gridCells, ans.c_str());
     }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
    if (OpenDialog1->Execute()) {
        AnsiString ans = OpenDialog1->FileName;
        readSavedGame(gridCells, ans.c_str());
        fillFromCells();
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::fillFromCells() {
     for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			StringGrid1->Cells[j][i] = gridCells[i][j].value == 0 ? "" : IntToStr(gridCells[i][j].value);
		}
	}
}
