#include <cmath>
#include "Pawn.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Pawn::Pawn(Square* square, bool isWhite) : Piece(square, isWhite), hasMoved(false) {}

vector<Move> Pawn::computeValidMoves(const Board& board) const {
	vector<Move> validMoves;

	Square* forwardSquare;
	Square* doubleForwardSquare;
	Square* leftDiagonal;
	Square* rightDiagonal;

	int forwardSquareId;
	int doubleForwardSquareId;
	int leftDiagonalId;
	int rightDiagonalId;

	//Considering forward
	forwardSquareId = square->id + (isWhite) ? 8 : -8;
	
	try {
		forwardSquare = board.getSquare(forwardSquareId);
	} catch (string error) {
		forwardSquare = nullptr;
	}

	bool forwardSquareIsValid = forwardSquare != nullptr && !forwardSquare->isOccupied;
	if (forwardSquareIsValid)
		validMoves.push_back(Move(square, forwardSquare));

	//Considering forward 2 spaces
	doubleForwardSquareId = square->id + (isWhite) ? 16 : -16;

	try {
		doubleForwardSquare = board.getSquare(doubleForwardSquareId);
	} catch (string error) {
		doubleForwardSquare = nullptr;
	}

	bool doubleForwardSquareIsValid = doubleForwardSquare != nullptr && !doubleForwardSquare->isOccupied;
	if (forwardSquareIsValid && doubleForwardSquareIsValid && !hasMoved)
		validMoves.push_back(Move(square, doubleForwardSquare, DoublePawn));

	//Considering left diagonal
	leftDiagonalId = square->id + (isWhite) ? 7 : -9;

	if (leftDiagonalId % static_cast<int>(round(sqrt(BOARD_SIZE))) == (isWhite) ? 0 : 7)
		leftDiagonalId = -1;

	try {
		leftDiagonal = board.getSquare(leftDiagonalId);
	} catch (string error) {
		leftDiagonal = nullptr;
	}

	if (leftDiagonal != nullptr && leftDiagonal->isOccupied && leftDiagonal->piece->isWhite != isWhite)
		validMoves.push_back(Move(square, leftDiagonal, Capture));

	//Considering right diagonal
	rightDiagonalId = square->id + (isWhite) ? 9: -7;

	if (rightDiagonalId % static_cast<int>(round(sqrt(BOARD_SIZE))) == (isWhite) ? 7 : 0)
		rightDiagonalId = -1;

	try {
		rightDiagonal = board.getSquare(rightDiagonalId);
	} catch (string error) {
		rightDiagonal = nullptr;
	}

	if (rightDiagonal != nullptr && rightDiagonal->isOccupied && rightDiagonal->piece->isWhite != isWhite)
		validMoves.push_back(Move(square, rightDiagonal, Capture));

	//Consider en passant (need to check last board move)

	return validMoves;
}