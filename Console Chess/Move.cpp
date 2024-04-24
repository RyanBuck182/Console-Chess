#include "Board.h"
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

Square* Move::getStartSquare() const {
	return startSquare;
}

Square* Move::getEndSquare() const {
	return endSquare;
}

Move::MoveType Move::getMoveType() const {
	return moveType;
}

void Move::setMoveType(MoveType moveType) {
	this->moveType = moveType;
}

bool Move::operator==(const Move& move) const {
	return startSquare == move.startSquare && endSquare == move.endSquare;
}

istream& operator>>(istream& in, Move*& move) {
	Square* startSquare = nullptr;
	Square* endSquare = nullptr;

	while (startSquare == nullptr) {
		cout << "  Start Square: ";

		try {
			cin >> startSquare;
		} catch (const char*) {
			cout << "Invalid input! Please input a valid square (e.g. a1).\n\n";
		}
	}

	while (endSquare == nullptr) {
		cout << "    End Square: ";

		try {
			cin >> endSquare;
		} catch (const char*) {
			cout << "Invalid input! Please input a valid square (e.g. a1).\n\n";
		}
	}

	move = new Move(startSquare, endSquare);

	if (!Board::moveIsValid(move))
		throw "Move is not valid.";

	return in;
}
