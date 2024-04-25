#include "Piece.h"
#include "Square.h"
#include "Move.h"

using namespace std;

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

vector<Square*> Piece::getAttackedSquares() {
	vector<Move*> validMoves = computeValidMoves();
	
	vector<Square*> attackedSquares;
	for (int i = 0; i < validMoves.size(); i++)
		attackedSquares.push_back(validMoves[i]->getEndSquare());

	return attackedSquares;
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