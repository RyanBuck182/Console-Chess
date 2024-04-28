/*
Modified By:    Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

#include "Piece.h"
#include "Square.h"
#include "Move.h"

using namespace std;

Piece::Piece(Board* board, Square* square, bool pieceIsWhite, char whitePieceSymbol, char blackPieceSymbol) {
	this->board = board;
	this->square = square;
	this->pieceIsWhite = pieceIsWhite;
	this->whitePieceSymbol = whitePieceSymbol;
	this->blackPieceSymbol = blackPieceSymbol;
}

Piece::~Piece() {
	board = nullptr;
	square = nullptr;
}

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

void Piece::makeMove(Move move) {
	makeStandardMove(move);
}

void Piece::makeStandardMove(Move move) {
	delete move.getEndSquare()->getPiece();
	square->setPiece(nullptr);
	move.getEndSquare()->setPiece(this);
	this->setSquare(move.getEndSquare());
}