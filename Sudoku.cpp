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
    std::vector<std::vector<int>> tmpCorr(9, std::vector<int>(9));
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
    tmpCorr = sudoku->getSolnGrid();

    Cell *tmpCell;
    std::vector<Cell> tmpV;
    for (int i = 0; i < 9; i++) {
        tmpV = std::vector<Cell>();
        gridCells.push_back(tmpV);
        for (int j = 0; j < 9; j++) {
            tmpCell = new Cell(tmp[i][j], tmpCorr[i][j]);
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
    isToBeHighlighted = false;
    Panel1->Color = clRed;
    //(TColor) RGB(46, 46, 46);
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
    a->Pen->Width = 1;
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
            a->Brush->Color = (TColor) RGB(214, 214, 214);
        else
		//if ((!State.Contains(gdFixed))&&(this->StringGrid1->Cells[ACol][ARow].ToInt()<0))
            a->Brush->Color = clWhite;
        if (gridCells[ARow][ACol].isHighlited) {
            a->Brush->Color = (TColor) RGB(197, 227, 244);
        }
        if (gridCells[ARow][ACol].isDupe) {
            a->Brush->Color = (TColor) RGB(255, 156, 156);
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
	a->Pen->Color = (TColor) RGB(105, 105, 105);  //HEX for this color is #696969
                                                  //NICE
	a->Rectangle(Rect.left,Rect.top,Rect.right,Rect.bottom);
    a->Font->Size = 16;
    //a->Font->Color = gridCells[ARow][ACol].isRedactable ? clBlue : clBlack;
	DrawText(a->Handle, this->StringGrid1->Cells[ACol][ARow].t_str(), -1, (TRect*)&r, DT_CENTER);

    a->Pen->Width = 4;
    a->Pen->Color = clBlack;
    a->MoveTo(150, 0);
    a->LineTo(150, 455);
    a->MoveTo(300, 0);
    a->LineTo(300, 455);

    a->MoveTo(0, 150);
    a->LineTo(455, 150);
    a->MoveTo(0, 300);
    a->LineTo(455, 300);
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
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            gridCells[i][j].isHighlited = false;
        }
    }
    if (isToBeHighlighted && gridCells[ARow][ACol].value != 0) {
        highlightGrid(gridCells[ARow][ACol].value);
    }
    CanSelect = gridCells[ARow][ACol].isRedactable;
}

void __fastcall TForm1::highlightGrid(int val) {
     for (int i = 0; i < 9; i++) {
         for (int j = 0; j < 9; j++) {
             gridCells[i][j].isHighlited = gridCells[i][j].value == val;
         }
     }
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
void __fastcall TForm1::N4Click(TObject *Sender)
{
     MessageDlg("Игровое поле представляет собой квадрат размером 9x9, разделённый на меньшие квадраты со стороной в 3 клетки.\nВ них уже в начале игры стоят некоторые числа (от 1 до 9).\nОт игрока требуется заполнить свободные клетки цифрами от 1 до 9 так, чтобы в каждой строке, в каждом столбце и в каждом малом квадрате 3x3 каждая цифра встречалась бы только один раз.", mtInformation, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

//void __fastcall TForm1::Button2Click(TObject *Sender)
//{
//     isToBeHighlighted = !isToBeHighlighted;
//     Button2->Caption = isToBeHighlighted ? "Выключить подсветку" : "Включить подсветку";
//}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender) {
    bool ans = true;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            ans &= gridCells[i][j].isCorrect();
        }
    }

    if (ans) {
        ShowMessage("Поздравляем! Вы победили!");
    }
}
//---------------------------------------------------------------------------

