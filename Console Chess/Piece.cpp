#include "Piece.h"
#include "Square.h"
#include "Move.h"

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

void Piece::makeMove(Move* move) {
	makeStandardMove(move);
}

void Piece::makeStandardMove(Move* move) {
	delete move->getEndSquare()->getPiece();
	move->getEndSquare()->setPiece(move->getStartSquare()->getPiece());
	move->getEndSquare()->getPiece()->setSquare(move->getEndSquare());
	move->getStartSquare()->setPiece(nullptr);
}

Piece::Piece(Square* square, bool pieceIsWhite, char whitePieceSymbol, char blackPieceSymbol) {
	this->square = square;
	this->pieceIsWhite = pieceIsWhite;
	this->whitePieceSymbol = whitePieceSymbol;
	this->blackPieceSymbol = blackPieceSymbol;
}