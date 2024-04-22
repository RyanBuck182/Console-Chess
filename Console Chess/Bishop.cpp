#include "Bishop.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"
using namespace std;

Bishop::Bishop(Square* square, bool isWhite) : Piece(square, isWhite, 'B', 'b') {}

vector<Move*>Bishop::computeValidMoves() const {
	vector<Move*> validMoves;

	// Check forward left diagonals.
	Square* squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getLeftSquare(Board::getForwardSquare(squareCursor));
			if (squareCursor->getIsOccupied())
				if (squareCursor->getPiece()->isWhite == isWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		} catch (const char* error) {
			squareCursor = nullptr;
		}
	}

	// Check forward right diagonals.
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getRightSquare(Board::getForwardSquare(squareCursor));
			if (squareCursor->getIsOccupied())
				if (squareCursor->getPiece()->isWhite == isWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		} catch (const char* error) {
			squareCursor = nullptr;
		}
	}

	// Check backward left diagonals.
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getLeftSquare(Board::getBackwardSquare(squareCursor));
			if (squareCursor->getIsOccupied())
				if (squareCursor->getPiece()->isWhite == isWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		} catch (const char* error) {
			squareCursor = nullptr;
		}
	}

	// Check backward right diagonals.
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getRightSquare(Board::getBackwardSquare(squareCursor));
			if (squareCursor->getIsOccupied())
				if (squareCursor->getPiece()->isWhite == isWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		} catch (const char* error) {
			squareCursor = nullptr;
		}
	}

	return validMoves;
}