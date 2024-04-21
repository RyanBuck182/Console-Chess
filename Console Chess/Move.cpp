#include "Move.h"
#include "Square.h"

Move::Move(Square* startSquare, Square* endSquare) {
	this->startSquare = startSquare;
	this->endSquare = endSquare;
}

bool Move::operator==(const Move& move) const {
	return startSquare == move.startSquare && endSquare == move.endSquare;
}