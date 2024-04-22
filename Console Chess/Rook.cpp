#include "Rook.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"
using namespace std;

Rook::Rook(Square* square, bool isWhite) : Piece(square, isWhite, 'R', 'r') {}
Rook:: ~Rook() {}

vector<Move*>Rook::computeValidMoves(const Board& board) const {
	vector<Move*> validMoves;

	// Check forward side of column.
	Square* squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = board.getForwardSquare(squareCursor);
			if (squareCursor->isOccupied)
				if (squareCursor->piece->isWhite == isWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		} catch (const char* error) {
			squareCursor = nullptr;
		}
	}

	// Check backward side of column
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = board.getBackwardSquare(squareCursor);
			if (squareCursor->isOccupied)
				if (squareCursor->piece->isWhite == isWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		} catch (const char* error) {
			squareCursor = nullptr;
		}
	}

	// Check left side of row
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = board.getLeftSquare(squareCursor);
			if (squareCursor->isOccupied)
				if (squareCursor->piece->isWhite == isWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		} catch (const char* error) {
			squareCursor = nullptr;
		}
	}

	// Check right side of row
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getRightSquare(squareCursor);
			if (squareCursor->isOccupied)
				if (squareCursor->piece->isWhite == isWhite)
					break;
				else
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
			else
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
		}
		catch (const char* error) {
			squareCursor = nullptr;
		}
	}

	return validMoves;
}