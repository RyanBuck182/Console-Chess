#include "Piece.h"
#include "Square.h"

Piece::Piece(Square* square, bool isWhite, char whitePieceSymbol, char blackPieceSymbol) {
	this->square = square;
	this->isWhite = isWhite;
	this->whitePieceSymbol = whitePieceSymbol;
	this->blackPieceSymbol = blackPieceSymbol;
}

Piece::~Piece() {}