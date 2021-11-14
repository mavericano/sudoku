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
#include <regex>
#include <vector>
#include "MapCreator.h"
#include "Cell.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TToggleSwitch *ToggleSwitch1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall StringGrid1SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);

private:	// User declarations
    void __fastcall fillGrid();
    void __fastcall validateGrid(int ACol, int ARow);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    std::vector<std::vector<Cell>> gridCells;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
