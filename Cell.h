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
        int correctValue;
        Cell();
        Cell(int value, int correctValue);
        bool isCorrect();
};
#endif
