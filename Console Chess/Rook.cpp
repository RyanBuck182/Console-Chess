#include "Rook.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Rook::Rook(Square* square, bool pieceIsWhite) : Piece(square, pieceIsWhite, 'R', 'r') {}

vector<Move*>Rook::computeValidMoves() const {
	vector<Move*> validMoves;

	// Check forward side of column.
	Square* squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getForwardSquare(squareCursor);
			if (squareCursor->isOccupied())
				if (squareCursor->getPiece()->isWhite() == pieceIsWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	// Check backward side of column
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getBackwardSquare(squareCursor);
			if (squareCursor->isOccupied())
				if (squareCursor->getPiece()->isWhite() == pieceIsWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	// Check left side of row
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getLeftSquare(squareCursor);
			if (squareCursor->isOccupied())
				if (squareCursor->getPiece()->isWhite() == pieceIsWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		} catch (const char*) {
			squareCursor = nullptr;
		}
	}

	// Check right side of row
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = Board::getRightSquare(squareCursor);
			if (squareCursor->isOccupied())
				if (squareCursor->getPiece()->isWhite() == pieceIsWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		}
		catch (const char*) {
			squareCursor = nullptr;
		}
	}

	return validMoves;
}