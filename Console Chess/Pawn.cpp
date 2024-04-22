#include "Pawn.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Pawn::Pawn(Square* square, bool isWhite) : Piece(square, isWhite, 'P', 'p'), hasMoved(false) {}

Pawn::~Pawn() {}

vector<Move*> Pawn::computeValidMoves(const Board& board) const {
	vector<Move*> validMoves;
	
	Move* lastMove;

	try {
		lastMove = board.getLastMove();
	} catch (const char* error) {
		lastMove = nullptr;
	}
	
	Square* forwardSquare;
	Square* doubleForwardSquare;
	Square* leftDiagonalSquare;
	Square* rightDiagonalSquare;

	//Considering forward
	try {
		forwardSquare = board.getForwardSquare(square);
	} catch (const char* error) {
		forwardSquare = nullptr;
	}

	bool forwardSquareIsValid = forwardSquare != nullptr && !forwardSquare->isOccupied;
	if (forwardSquareIsValid)
		validMoves.push_back(new Move(square, forwardSquare));

	//Considering forward 2 spaces
	try {
		doubleForwardSquare = board.getForwardSquare(forwardSquare);
	} catch (const char* error) {
		doubleForwardSquare = nullptr;
	}

	bool doubleForwardSquareIsValid = doubleForwardSquare != nullptr && !doubleForwardSquare->isOccupied;
	if (forwardSquareIsValid && doubleForwardSquareIsValid && !hasMoved)
		validMoves.push_back(new Move(square, doubleForwardSquare, Move::DoublePawn));

	//Considering left diagonal
	try {
		leftDiagonalSquare = board.getLeftSquare(board.getForwardSquare(square));
	} catch (const char* error) {
		leftDiagonalSquare = nullptr;
	}

	if (leftDiagonalSquare != nullptr) {
		bool leftDiagonalCaptureIsValid = leftDiagonalSquare->isOccupied && leftDiagonalSquare->piece->isWhite != isWhite;
 		bool leftDiagonalEnPassantIsValid = lastMove != nullptr && lastMove->moveType == Move::DoublePawn && board.getBackwardSquare(lastMove->endSquare) == leftDiagonalSquare;

		if (leftDiagonalCaptureIsValid)
			validMoves.push_back(new Move(square, leftDiagonalSquare, Move::Capture));
		else if (leftDiagonalEnPassantIsValid)
			validMoves.push_back(new Move(square, leftDiagonalSquare, Move::EnPassant));
	}

	//Considering right diagonal
	try {
		rightDiagonalSquare = board.getRightSquare(board.getForwardSquare(square));
	} catch (const char* error) {
		rightDiagonalSquare = nullptr;
	}

	if (rightDiagonalSquare != nullptr) {
		bool rightDiagonalCaptureIsValid = rightDiagonalSquare->isOccupied && rightDiagonalSquare->piece->isWhite != isWhite;
		bool rightDiagonalEnPassantIsValid = lastMove != nullptr && lastMove->moveType == Move::DoublePawn && board.getBackwardSquare(lastMove->endSquare) == rightDiagonalSquare;

		if (rightDiagonalCaptureIsValid)
			validMoves.push_back(new Move(square, rightDiagonalSquare, Move::Capture));
		else if (rightDiagonalEnPassantIsValid)
			validMoves.push_back(new Move(square, rightDiagonalSquare, Move::EnPassant));
	}

	return validMoves;
}