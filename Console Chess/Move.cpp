#include "Move.h"
#include "Square.h"

using namespace std;

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

Move::~Move() {
	delete startSquare;
	startSquare = nullptr;

	delete endSquare;
	endSquare = nullptr;
}

bool Move::operator==(const Move& move) const {
	return startSquare == move.startSquare && endSquare == move.endSquare;
}