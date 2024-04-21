#include "Move.h"
#include "Square.h"

Move::Move(Square* startSquare, Square* endSquare) {
	this->startSquare = startSquare;
	this->endSquare = endSquare;
}