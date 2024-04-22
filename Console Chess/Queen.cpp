#include "Queen.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Queen::Queen(Square* square, bool isWhite) : Piece(square, isWhite, 'Q', 'q') {}
Queen::~Queen() {}

vector<Move*>Queen::computeValidMoves() const 
{
	vector<Move*> validMoves;

	// Check forward side of column.
	Square* squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getForwardSquare(squareCursor);
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

	// Check backward side of column.
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getBackwardSquare(squareCursor);
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

	// Check left side of row.
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getLeftSquare(squareCursor);
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

	// Check right side of row.
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getRightSquare(squareCursor);
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

	// Check forward left diagonals.
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getLeftSquare(Board::getForwardSquare(squareCursor));
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

	// Check forward right diagonals.
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getRightSquare(Board::getForwardSquare(squareCursor));
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

	// Check backward left diagonals.
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getLeftSquare(Board::getBackwardSquare(squareCursor));
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

	// Check backward right diagonals.
	squareCursor = square;
	while (squareCursor != nullptr) {
		try {
			squareCursor = Board::getRightSquare(Board::getBackwardSquare(squareCursor));
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

	return validMoves;
}