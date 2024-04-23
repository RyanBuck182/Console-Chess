#include "Pawn.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Pawn::Pawn(Square* square, bool pieceIsWhite) : Piece(square, pieceIsWhite, 'P', 'p'), hasMoved(false) {}

vector<Move*> Pawn::computeValidMoves() const {
	vector<Move*> validMoves;
	
	Move* lastMove;

	try {
		lastMove = Board::getLastMove();
	} catch (const char*) {
		lastMove = nullptr;
	}
	
	Square* forwardSquare;
	Square* doubleForwardSquare;
	Square* leftDiagonalSquare;
	Square* rightDiagonalSquare;

	//Considering forward
	try {
		forwardSquare = Board::getForwardSquare(square);
	} catch (const char*) {
		forwardSquare = nullptr;
	}

	bool forwardSquareIsValid = forwardSquare != nullptr && !forwardSquare->isOccupied();
	if (forwardSquareIsValid)
		validMoves.push_back(new Move(square, forwardSquare));

	//Considering forward 2 spaces
	try {
		doubleForwardSquare = Board::getForwardSquare(forwardSquare);
	} catch (const char*) {
		doubleForwardSquare = nullptr;
	}

	bool doubleForwardSquareIsValid = doubleForwardSquare != nullptr && !doubleForwardSquare->isOccupied();
	if (forwardSquareIsValid && doubleForwardSquareIsValid && !hasMoved)
		validMoves.push_back(new Move(square, doubleForwardSquare, Move::DoublePawn));

	//Considering left diagonal
	try {
		leftDiagonalSquare = Board::getLeftSquare(Board::getForwardSquare(square));
	} catch (const char*) {
		leftDiagonalSquare = nullptr;
	}

	if (leftDiagonalSquare != nullptr) {
		bool leftDiagonalCaptureIsValid = leftDiagonalSquare->isOccupied() && leftDiagonalSquare->getPiece()->isWhite() != pieceIsWhite;
 		bool leftDiagonalEnPassantIsValid = lastMove != nullptr && lastMove->getMoveType() == Move::DoublePawn && *Board::getLeftSquare(square) == *lastMove->getEndSquare();

		if (leftDiagonalCaptureIsValid)
			validMoves.push_back(new Move(square, leftDiagonalSquare, Move::Capture));
		else if (leftDiagonalEnPassantIsValid)
			validMoves.push_back(new Move(square, leftDiagonalSquare, Move::EnPassant));
	}

	//Considering right diagonal
	try {
		rightDiagonalSquare = Board::getRightSquare(Board::getForwardSquare(square));
	} catch (const char*) {
		rightDiagonalSquare = nullptr;
	}

	if (rightDiagonalSquare != nullptr) {
		bool rightDiagonalCaptureIsValid = rightDiagonalSquare->isOccupied() && rightDiagonalSquare->getPiece()->isWhite() != pieceIsWhite;
		bool rightDiagonalEnPassantIsValid = lastMove != nullptr && lastMove->getMoveType() == Move::DoublePawn && *Board::getRightSquare(square) == *lastMove->getEndSquare();

		if (rightDiagonalCaptureIsValid)
			validMoves.push_back(new Move(square, rightDiagonalSquare, Move::Capture));
		else if (rightDiagonalEnPassantIsValid)
			validMoves.push_back(new Move(square, rightDiagonalSquare, Move::EnPassant));
	}

	return validMoves;
}