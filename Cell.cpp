//---------------------------------------------------------------------------

#pragma hdrstop

#include "Cell.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Cell::Cell() {
    this->isDupe = false;
    this->isHighlited = false;
    this->isRedactable = false;
    this->value = 0;
    this->correctValue = 0;
}

Cell::Cell(int value, int correctValue) {
    this->isDupe = false;
    this->isHighlited = false;
    this->isRedactable = false;
    this->value = value;
    this->correctValue = correctValue;
}

bool Cell::isCorrect() {
     return value == correctValue;
}