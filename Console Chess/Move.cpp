#include "Board.h"
#include "Move.h"
#include "Square.h"

using namespace std;

Move::Move(Board* board) {
	this->board = board;
	startSquare = nullptr;
	endSquare = nullptr;
	moveType = Standard;
}

Move::Move(Board* board, Square* startSquare, Square* endSquare) {
	this->board = board;
	this->startSquare = startSquare;
	this->endSquare = endSquare;
	moveType = Standard;
}

Move::Move(Board* board, Square* startSquare, Square* endSquare, MoveType moveType) {
	this->board = board;
	this->startSquare = startSquare;
	this->endSquare = endSquare;
	this->moveType = moveType;
}

Move::~Move() {
	board = nullptr;
	startSquare = nullptr;
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

ostream& operator<<(ostream& out, const Move& move)
{
	int startRow;
	int endRow;
	char startColumn;
	char endColumn;

	startRow = (move.getStartSquare()->getId() / 8) + 1;
	endRow = (move.getEndSquare()->getId() / 8) + 1;

	startColumn = static_cast<char>(move.getStartSquare()->getId() % 8 + 97);
	endColumn =  static_cast<char>(move.getEndSquare()->getId() % 8 + 97);
	
	out << startColumn << startRow << " " << endColumn << endRow;

	return out;
}
istream& operator>>(istream& in, Move& move) {
	Square* startSquare = new Square(move.board);
	Square* endSquare = new Square(move.board);

	while (startSquare->getId() == -1) {
		cout << "Start Square: ";

		try {
			cin >> startSquare;
		} catch (const char*) {
			cout << "Invalid input! Please input a valid square (e.g. a1).\n\n";
		}
	}

	while (endSquare->getId() == -1) {
		cout << "  End Square: ";

		try {
			cin >> endSquare;
		} catch (const char*) {
			cout << "Invalid input! Please input a valid square (e.g. a1).\n\n";
		}
	}

	move = Move(move.board, startSquare, endSquare);

	if (!move.getStartSquare()->getBoard()->moveIsValid(move))
		throw "Move is not valid.";

	return in;
}
