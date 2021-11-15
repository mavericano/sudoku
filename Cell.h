//---------------------------------------------------------------------------

#ifndef CellH
#define CellH
//---------------------------------------------------------------------------
class Cell {
    public:
        bool isDupe;
        bool isHighlited;
        bool isRedactable;
        int value;
        Cell();
        Cell(int value);
};
#endif
