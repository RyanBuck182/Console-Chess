#include "Square.h"
#include "Piece.h"
#include "Board.h"

using namespace std;

Square::Square(int id)
{
	this->id = id;
	this->piece = nullptr;
}

Square::Square(int id, Piece* piece)
{
	this->id = id;
	setPiece(piece);
}

Square::~Square() {
	if (piece != nullptr) {
		piece->setSquare(nullptr);
		delete piece;
		piece = nullptr;
	}
}

int Square::getId() const {
	return id;
}

Piece* Square::getPiece() const {
	return piece;
}

void Square::setPiece(Piece* piece) {
	this->piece = piece;
}

bool Square::isOccupied() const {
	return piece != nullptr;
}

bool Square::operator==(const Square& square) {
	return id == square.id;
}

istream& operator>>(istream& in, Square*& square) {
	char column;
	int row;

	cin >> column;
	cin >> row;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	int id = (row - 1) * Board::BOARD_LENGTH + (static_cast<int>(tolower(column) - static_cast<int>('a')));

	square = Board::getSquareFromId(id);

	return in;
}