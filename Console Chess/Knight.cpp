/*
Modified By:    Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

#include "Knight.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Knight::Knight(Board* board, Square* square, bool pieceIsWhite) : Piece(board, square, pieceIsWhite, 'N', 'n') {}

vector<Move> Knight::computeValidMoves() const {
	vector<Move> validMoves;
	vector<Square*> potentialEndSquares = getAttackedSquares();

	// Determining valid moves
	for (int i = 0; i < potentialEndSquares.size(); i++) {
		if (potentialEndSquares[i]->isOccupied()) {
			if (potentialEndSquares[i]->getPiece()->isWhite() != pieceIsWhite)
				validMoves.push_back(Move(board, square, potentialEndSquares[i], Move::Capture));
		} else
			validMoves.push_back(Move(board, square, potentialEndSquares[i], Move::Standard));
	}

	return validMoves;
}

vector<Square*> Knight::getAttackedSquares() const {
	vector<Square*> attackedSquares;

	// Forward left
	try {
		attackedSquares.push_back(square->getForwardSquare()->getForwardSquare()->getLeftSquare());
	} catch (const char*) {}

	// Forward right
	try {
		attackedSquares.push_back(square->getForwardSquare()->getForwardSquare()->getRightSquare());
	} catch (const char*) {}

	// Left forward
	try {
		attackedSquares.push_back(square->getLeftSquare()->getLeftSquare()->getForwardSquare());
	} catch (const char*) {}

	// Left backward
	try {
		attackedSquares.push_back(square->getLeftSquare()->getLeftSquare()->getBackwardSquare());
	} catch (const char*) {}

	// Right forward
	try {
		attackedSquares.push_back(square->getRightSquare()->getRightSquare()->getForwardSquare());
	} catch (const char*) {}

	// Right backward
	try {
		attackedSquares.push_back(square->getRightSquare()->getRightSquare()->getBackwardSquare());
	} catch (const char*) {}

	// Backward left
	try {
		attackedSquares.push_back(square->getBackwardSquare()->getBackwardSquare()->getLeftSquare());
	} catch (const char*) {}

	// Backward right
	try {
		attackedSquares.push_back(square->getBackwardSquare()->getBackwardSquare()->getRightSquare());
	} catch (const char*) {}

	return attackedSquares;
}