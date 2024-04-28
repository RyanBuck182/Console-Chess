/*
Modified By:    Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

#include "Rook.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Rook::Rook(Board* board, Square* square, bool pieceIsWhite) : Piece(board, square, pieceIsWhite, 'R', 'r'), pieceHasMoved(false) {}

bool Rook::hasMoved() const {
	return pieceHasMoved;
}

vector<Move>Rook::computeValidMoves() const {
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

vector<Square*> Rook::getAttackedSquares() const {
	vector<Square*> attackedSquares;

	// Check forward side of column
	Square* squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = squareCursor->getForwardSquare();
			attackedSquares.push_back(squareCursor);
			if (squareCursor->isOccupied())
				squareCursor = nullptr;
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	// Check backward side of column
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = squareCursor->getBackwardSquare();
			attackedSquares.push_back(squareCursor);
			if (squareCursor->isOccupied())
				squareCursor = nullptr;
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	// Check left side of row
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = squareCursor->getLeftSquare();
			attackedSquares.push_back(squareCursor);
			if (squareCursor->isOccupied())
				squareCursor = nullptr;
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	// Check right side of row
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = squareCursor->getRightSquare();
			attackedSquares.push_back(squareCursor);
			if (squareCursor->isOccupied())
				squareCursor = nullptr;
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	return attackedSquares;
}
