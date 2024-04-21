#include <cmath>
#include "Pawn.h"
#include "Square.h"
#include "Board.h"

Pawn::Pawn(Square* square, bool isWhite) : Piece(square, isWhite), hasMoved(false) {}

vector<Move> Pawn::getValidMoves(const Board& board) const {
	vector<Move> validMoves;

	Square* forwardSquare;
	Square* leftDiagonal;
	Square* rightDiagonal;

	int forwardSquareId;
	int leftDiagonalId;
	int rightDiagonalId;

	//Considering forward
	forwardSquareId = square->id + (isWhite) ? 8 : -8;
	
	try {
		forwardSquare = board.getSquare(forwardSquareId);
	} catch (string error) {
		forwardSquare = nullptr;
	}

	if (forwardSquare != nullptr && !forwardSquare->isOccupied)
		validMoves.push_back(Move(square, forwardSquare));

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
		validMoves.push_back(Move(square, leftDiagonal));

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
		validMoves.push_back(Move(square, rightDiagonal));

	//Consider en passant (need to check last board move)
	//Consider moving forward 2 spaces (need to check if it's the pawn's first move)

	return validMoves;
}