#include "Square.h"
#include "Piece.h"

Square::Square(int id)
{
	this->id = id;
	this->piece = nullptr;
	isOccupied = false;
}

Square::Square(int id, Piece* piece)
{
	this->id = id;
	setPiece(piece);
}

Square::~Square() {
	if (piece != nullptr) {
		piece->square = nullptr;
		delete piece;
		piece = nullptr;
	}
}

void Square::setPiece(Piece* piece) {
	this->piece = piece;
	isOccupied = (piece != nullptr) ? true : false;
}

bool Square::operator==(const Square& square) {
	return id == square.id;
}