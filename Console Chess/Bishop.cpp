#include "Bishop.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"
using namespace std;

Bishop::Bishop(Square* square, bool isWhite) : Piece(square, isWhite, 'B', 'b'){}

vector<Move*>Bishop::computeValidMoves(const Board& board) const
{
	vector<Move*> validMoves;

	Square* squareCursor = square;
	// forward right
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getForwardSquare(board.getRightSquare(squareCursor));
			if (squareCursor->isOccupied)
			{
				if (squareCursor->piece->isWhite == isWhite)
				{
					break;
				}
				else {
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
				}
			}
			else {
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
			}

		}
		catch (const char* error) {
			squareCursor = nullptr;
		}
	}
	// backwards right
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getBackwardSquare(board.getRightSquare(squareCursor));
			if (squareCursor->isOccupied)
			{
				if (squareCursor->piece->isWhite == isWhite)
				{
					break;
				}
				else {
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
				}
			}
			else {
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
			}

		}
		catch (const char* error) {
			squareCursor = nullptr;
		}
	}
	// forward left
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getForwardSquare(board.getLeftSquare(squareCursor));
			if (squareCursor->isOccupied)
			{
				if (squareCursor->piece->isWhite == isWhite)
				{
					break;
				}
				else {
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
				}
			}
			else {
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
			}

		}
		catch (const char* error) {
			squareCursor = nullptr;
		}
	}
	// backwards left
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getBackwardSquare(board.getLeftSquare(squareCursor));
			if (squareCursor->isOccupied)
			{
				if (squareCursor->piece->isWhite == isWhite)
				{
					break;
				}
				else {
					validMoves.push_back(new Move(square, squareCursor, Move::Capture));
				}
			}
			else {
				validMoves.push_back(new Move(square, squareCursor, Move::Standard));
			}

		}
		catch (const char* error) {
			squareCursor = nullptr;
		}
	}

	return validMoves;
}