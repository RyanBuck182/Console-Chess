#include "Move.h"
#include "Square.h"

Move::Move(Square* startSquare, Square* endSquare) {
	this->startSquare = startSquare;
	this->endSquare = endSquare;
	moveType = Standard;
}

Move::Move(Square* startSquare, Square* endSquare, MoveType moveType) {
	this->startSquare = startSquare;
	this->endSquare = endSquare;
	this->moveType = moveType;
}

bool Move::operator==(const Move& move) const {
	return startSquare == move.startSquare
		&& endSquare == move.endSquare
		&& moveType == move.moveType;
}