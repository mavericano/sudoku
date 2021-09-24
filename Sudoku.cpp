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

	getGrid(tmp);

	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			StringGrid1->Cells[j][i] = tmp[i][j];
		}
	}
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    init();
	StringGrid1->DefaultDrawing = false;
	StringGrid1->DoubleBuffered = true;
	fillGrid();
	//ShowMessage(IntToStr(returnHello()));
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
	if (State.Contains(gdFixed)) a->Brush->Color = clMoneyGreen;

	//��� ��� � ��� ������� �������, �.�. ���� ������ ����, ���� ������ ����� ����� ���
	//� ���� .ToInt() �����, �� ������ ���� ��� ��������� �������� ToDouble.
	try
	{
		if ((!State.Contains(gdFixed))&&(this->StringGrid1->Cells[ACol][ARow].ToInt()>0)) a->Brush->Color = clRed;
		if ((!State.Contains(gdFixed))&&(this->StringGrid1->Cells[ACol][ARow].ToInt()<0)) a->Brush->Color = clGreen;
	}catch(...)
	{
		//try ����� ��� ���� ��� �� ���� ����� � ����� ������ ����� ��������, ����� �� �� ������� �� �����
	}


	//���, �� ���������� ������� ����������, ������ �����������
	a->FillRect(Rect);

	//��� �������� ��� ��� �� ��������� ��������
	//����� ������ ������ ��������
	if (State.Contains(gdSelected))
	{
		a->Pen->Color = clLime;
		a->Rectangle(Rect);
	}



	//�����, ��� ��� DefaultDrawing = False; ���������� ��� � ����� ����������.
	//����� ����������� TextRect
	//a->TextRect(Rect,Rect.left,Rect.top,this->StringGrid1->Cells[ACol][ARow]);
	//�� ��� �������� ������ DrawText - �������� ���� � �������, � ��� ������������� ������ ����� ������������� � ������ ������.
	//TRect - ������ ��������.
	TRect r = Rect;
	r.left +=2;
	r.top+=2;
	DrawText(a->Handle,this->StringGrid1->Cells[ACol][ARow].t_str(),-1,(TRect*)&r,DT_CENTER);

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1SetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value)
{
	const auto r = std::regex(R"([1-9]{1})");
	AnsiString tmp = Value;
	StringGrid1->Cells[ACol][ARow] = std::regex_match(tmp.c_str(), r) ? Value : "";
}
//---------------------------------------------------------------------------

