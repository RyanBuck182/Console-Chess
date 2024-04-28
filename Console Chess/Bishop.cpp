/*
Modified By:    Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

#include "Bishop.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"
using namespace std;

Bishop::Bishop(Board* board, Square* square, bool pieceIsWhite) : Piece(board, square, pieceIsWhite, 'B', 'b') {}

vector<Move>Bishop::computeValidMoves() const {
	vector<Move> validMoves;
	vector<Square*> potentialEndSquares = getAttackedSquares();

	for (int i = 0; i < potentialEndSquares.size(); i++) {
		if (potentialEndSquares[i]->isOccupied()) {
			if (potentialEndSquares[i]->getPiece()->isWhite() != pieceIsWhite)
				validMoves.push_back(Move(board, square, potentialEndSquares[i], Move::Capture));
		} else
			validMoves.push_back(Move(board, square, potentialEndSquares[i], Move::Standard));
	}

	return validMoves;
}

vector<Square*> Bishop::getAttackedSquares() const {
	vector<Square*> attackedSquares;

	// Check forward left diagonals
	Square* squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = squareCursor->getForwardSquare()->getLeftSquare();
			attackedSquares.push_back(squareCursor);
			if (squareCursor->isOccupied())
				squareCursor = nullptr;
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	// Check forward right diagonals
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = squareCursor->getForwardSquare()->getRightSquare();
			attackedSquares.push_back(squareCursor);
			if (squareCursor->isOccupied())
				squareCursor = nullptr;
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	// Check backward left diagonals
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = squareCursor->getBackwardSquare()->getLeftSquare();
			attackedSquares.push_back(squareCursor);
			if (squareCursor->isOccupied())
				squareCursor = nullptr;
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	// Check backward right diagonals
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = squareCursor->getBackwardSquare()->getRightSquare();
			attackedSquares.push_back(squareCursor);
			if (squareCursor->isOccupied())
				squareCursor = nullptr;
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	return attackedSquares;
}
