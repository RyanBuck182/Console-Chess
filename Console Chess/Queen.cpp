#include "Queen.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Queen::Queen(Board* board, Square* square, bool pieceIsWhite) : Piece(board, square, pieceIsWhite, 'Q', 'q') {}

vector<Move*>Queen::computeValidMoves() const {
	vector<Move*> validMoves;
	vector<Square*> potentialEndSquares = getAttackedSquares();
	
	for (int i = 0; i < potentialEndSquares.size(); i++) {
		if (potentialEndSquares[i]->isOccupied()) {
			if (potentialEndSquares[i]->getPiece()->isWhite() != pieceIsWhite)
				validMoves.push_back(new Move(board, square, potentialEndSquares[i], Move::Capture));
		} else
			validMoves.push_back(new Move(board, square, potentialEndSquares[i], Move::Standard));
	}

	return validMoves;
}

vector<Square*> Queen::getAttackedSquares() const {
	vector<Square*> attackedSquares;

	// Check forward side of column
	Square* squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = board->getForwardSquare(squareCursor);
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
			squareCursor = board->getBackwardSquare(squareCursor);
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
			squareCursor = board->getLeftSquare(squareCursor);
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
			squareCursor = board->getRightSquare(squareCursor);
			attackedSquares.push_back(squareCursor);
			if (squareCursor->isOccupied())
				squareCursor = nullptr;
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	// Check forward left diagonals
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = board->getLeftSquare(board->getForwardSquare(squareCursor));
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
			squareCursor = board->getRightSquare(board->getForwardSquare(squareCursor));
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
			squareCursor = board->getLeftSquare(board->getBackwardSquare(squareCursor));
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
			squareCursor = board->getRightSquare(board->getBackwardSquare(squareCursor));
			attackedSquares.push_back(squareCursor);
			if (squareCursor->isOccupied())
				squareCursor = nullptr;
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	return attackedSquares;
}
