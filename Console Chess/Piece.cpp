#include "Piece.h"

Piece::Piece(Square* square, bool isWhite, char whitePieceSymbol, char blackPieceSymbol) {
	this->square = square;
	this->isWhite = isWhite;
	this->whitePieceSymbol = whitePieceSymbol;
	this->blackPieceSymbol = blackPieceSymbol;
}