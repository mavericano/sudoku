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
    sudoku->createSeed();
    sudoku->genPuzzle();
    sudoku->calculateDifficulty();
	tmp = sudoku->getGrid();

	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			StringGrid1->Cells[j][i] = tmp[i][j] == 0 ? 0 : tmp[i][j];
		}
	}

    Cell *tmpCell;
    std::vector<Cell> tmpV;
    for (int i = 0; i < 9; i++) {
        tmpV = std::vector<Cell>();
        gridCells.push_back(tmpV);
        for (int j = 0; j < 9; j++) {
            tmpCell = new Cell(tmp[i][j]);
            if (tmpCell->value != 0) {
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
}

//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
	//��� ��������
	TCanvas *a = this->StringGrid1->Canvas;
	//����� ���������� ���������� ����������� �����, �� ��� � ���� �����, ���� ������� �� �����������
	//���� ��� � ���� ����� ���� �� �������� ������ ���� �� ����� ����.
	a->Brush->Color = clWhite;
	//������, � ��� ������ ������ ���� �����
	//1. ������������� - ��� ����� ����� �������� fixed gdFixed
	//2. ���������� - ����� ��������� gdSelected
	//3. � "���������������" - ��� �� ������� � ���� ����� ������ gdFocused
	//�� ��� ��������� �������� ���������� State

	//������ ������ ���� ��� ������������� ������
	if (State.Contains(gdFixed))
       a->Brush->Color = clMoneyGreen;

	//��� ��� � ��� ������� �������, �.�. ���� ������ ����, ���� ������ ����� ����� ���
	//� ���� .ToInt() �����, �� ������ ���� ��� ��������� �������� ToDouble.
	try {
		if (gridCells[ARow][ACol].isRedactable)
        //(this->StringGrid1->Cells[ACol][ARow].ToInt()>0))
            a->Brush->Color = (TColor) RGB(205, 197, 194);
        else
		//if ((!State.Contains(gdFixed))&&(this->StringGrid1->Cells[ACol][ARow].ToInt()<0))
            a->Brush->Color = clWhite;
        if (gridCells[ARow][ACol].isDupe) {
           a->Brush->Color = clRed;
           ShowMessage(IntToStr(ACol) + " " + IntToStr(ARow) + " isDupe(");
        }
	} catch(...) {
		//try ����� ��� ���� ��� �� ���� ����� � ����� ������ ����� ��������, ����� �� �� ������� �� �����
	}

    //��� �������� ��� ��� �� ��������� ��������
	//����� ������ ������ ��������
    if (State.Contains(gdSelected)) {
       a->Brush->Color = (TColor) RGB(154, 206, 235);
       //a->Pen->Color = clBlue;
       //a->Rectangle(Rect);
	}

	//���, �� ���������� ������� ����������, ������ �����������
	a->FillRect(Rect);
	//�����, ��� ��� DefaultDrawing = False; ���������� ��� � ����� ����������.
	//����� ����������� TextRect
	//a->TextRect(Rect,Rect.left,Rect.top,this->StringGrid1->Cells[ACol][ARow]);
	//�� ��� �������� ������ DrawText - �������� ���� � �������, � ��� ������������� ������ ����� ������������� � ������ ������.
	//TRect - ������ ��������.
	TRect r = Rect;
	r.left += 2;
	r.top += 2;
	a->Pen->Color = clBlack;
	a->Rectangle(Rect.left,Rect.top,Rect.right,Rect.bottom);
	DrawText(a->Handle, this->StringGrid1->Cells[ACol][ARow].t_str(), -1, (TRect*)&r, DT_CENTER);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1SetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value)
{
    if (!
    gridCells[ARow][ACol].isRedactable) {
       ShowMessage("nope");
       StringGrid1->Cells[ACol][ARow] = IntToStr(gridCells[ARow][ACol].value);
       return;
    }
    if (Value != "") {
        const auto r = std::regex(R"([1-9]{1})");
        AnsiString tmp = Value;
        StringGrid1->Cells[ACol][ARow] = std::regex_match(tmp.c_str(), r) ? Value : "";
        //ShowMessage(StringGrid1->Cells[ACol][ARow]);
        validateGrid();
        //StringGrid1->Cells[0][0] = "hi";
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

     for (int block_num=0; block_num<9; ++block_num) {
         bool nums[10]={false};
         for (int cell_num=0; cell_num<9; ++cell_num) {
             int curr_num = gridCells[((int)(block_num/3))*3 + (cell_num/3)][((int)(block_num%3))*3 + (cell_num%3)].value;
             if(curr_num!=UNASSIGNED && nums[curr_num]==true) {
                 gridCells[((int)(block_num/3))*3 + (cell_num/3)][((int)(block_num%3))*3 + (cell_num%3)].isDupe = true;
                 //grid_status=false;
                 //return;
             }
             nums[curr_num] = true;
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
}
//---------------------------------------------------------------------------

