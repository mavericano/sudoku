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
	if (State.Contains(gdFixed)) a->Brush->Color = clMoneyGreen;

	//Так как у нас простое условие, т.е. либо больше нуля, либо меньше тогда будет так
	//У меня .ToInt() стоит, ты можешь твой тип поставить например ToDouble.
	try
	{
		if ((!State.Contains(gdFixed))&&(this->StringGrid1->Cells[ACol][ARow].ToInt()>0)) a->Brush->Color = clRed;
		if ((!State.Contains(gdFixed))&&(this->StringGrid1->Cells[ACol][ARow].ToInt()<0)) a->Brush->Color = clGreen;
	}catch(...)
	{
		//try Нужен для того что бы если вдруг в твоей яцейки текст окажется, тогда он ее красить не будет
	}


	//Все, мы установили устовия расскраски, теперь закрациваем
	a->FillRect(Rect);

	//тут дополнил еще что бы выделение работало
	//будет ячейку рамной обводить
	if (State.Contains(gdSelected))
	{
		a->Pen->Color = clLime;
		a->Rectangle(Rect);
	}



	//Далее, так как DefaultDrawing = False; необходимо еще и текст напечатать.
	//можно стандартным TextRect
	//a->TextRect(Rect,Rect.left,Rect.top,this->StringGrid1->Cells[ACol][ARow]);
	//но мне нравится больше DrawText - описание есть в справке, в нем расположенние текста можно устанавливать и многое другое.
	//TRect - делает смещение.
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

