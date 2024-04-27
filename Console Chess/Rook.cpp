#include "Rook.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Rook::Rook(Board* board, Square* square, bool pieceIsWhite) : Piece(board, square, pieceIsWhite, 'R', 'r'), pieceHasMoved(false) {}

Piece* Rook::clone(Board* newBoard, Square* newSquare) const {
	Piece* piece = new Rook(newBoard, newSquare, pieceIsWhite);
	newSquare->setPiece(piece);
	return piece;
}

bool Rook::hasMoved() const {
	return pieceHasMoved;
}

vector<Move*>Rook::computeValidMoves() const {
	vector<Move*> validMoves;
	vector<Square*> potentialEndSquares = getAttackedSquares();

	for (int i = 0; i < potentialEndSquares.size(); i++) {
		if (potentialEndSquares[i]->isOccupied()) {
			if (potentialEndSquares[i]->getPiece()->isWhite() != pieceIsWhite)
				validMoves.push_back(new Move(board, square, potentialEndSquares[i], Move::Capture));
		} else
			validMoves.push_back(new Move(board, square, potentialEndSquares[i], Move::Standard));
	}

	//add additional castling check

	return validMoves;
}

vector<Square*> Rook::getAttackedSquares() const {
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

	return attackedSquares;
}
