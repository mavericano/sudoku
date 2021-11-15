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
}

Cell::Cell(int value) {
    this->isDupe = false;
    this->isHighlited = false;
    this->isRedactable = false;
    this->value = value;
}