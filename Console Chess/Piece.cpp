#include "Piece.h"
#include "Square.h"

Square* Piece::getSquare() const {
	return square;
}

void Piece::setSquare(Square* square) {
	this->square = square;
}

bool Piece::isWhite() const {
	return pieceIsWhite;
}

char Piece::getPieceSymbol() const {
	return (pieceIsWhite) ? whitePieceSymbol : blackPieceSymbol;
}

Piece::Piece(Square* square, bool pieceIsWhite, char whitePieceSymbol, char blackPieceSymbol) {
	this->square = square;
	this->pieceIsWhite = pieceIsWhite;
	this->whitePieceSymbol = whitePieceSymbol;
	this->blackPieceSymbol = blackPieceSymbol;
}