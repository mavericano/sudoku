//---------------------------------------------------------------------------
#ifndef SudokuH
#define SudokuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <regex>
#include <vector>
#include "MapCreator.h"
#include "Cell.h"
#include "SudokuGenerator.h"
#include "FileHandler.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TToggleSwitch *ToggleSwitch1;
    TMainMenu *MainMenu1;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall StringGrid1SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
    void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
    void __fastcall N2Click(TObject *Sender);
    void __fastcall N3Click(TObject *Sender);

private:	// User declarations
    void __fastcall fillGrid();
    void __fastcall validateGrid();
    void __fastcall fillFromCells();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    std::vector<std::vector<Cell>> gridCells;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
