#include "Knight.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"
using namespace std;

Knight::Knight(Square* square, bool isWhite) : Piece(square, isWhite, 'N', 'n') {}
Knight::~Knight() {}

vector<Move*>Knight::computeValidMoves(const Board& board) const
{
	vector<Move*> validMoves;

	// up up right
	Square* squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getForwardSquare(board.getForwardSquare(board.getRightSquare(squareCursor)));
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

	// up up left
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getForwardSquare(board.getForwardSquare(board.getLeftSquare(squareCursor)));
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

	// right right up
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getRightSquare(board.getRightSquare(board.getForwardSquare(squareCursor)));
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

	// right right down
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getRightSquare(board.getRightSquare(board.getBackwardSquare(squareCursor)));
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

	// back back left
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getBackwardSquare(board.getBackwardSquare(board.getLeftSquare(squareCursor)));
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

	// back back right
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getBackwardSquare(board.getBackwardSquare(board.getRightSquare(squareCursor)));
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

	// left left up
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getLeftSquare(board.getLeftSquare(board.getForwardSquare(squareCursor)));
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

	// left left down
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getLeftSquare(board.getLeftSquare(board.getBackwardSquare(squareCursor)));
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