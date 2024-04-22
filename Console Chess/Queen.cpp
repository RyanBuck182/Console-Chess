#include "Queen.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"
using namespace std;

Queen::Queen(Square* square, bool isWhite) : Piece(square, isWhite, 'Q', 'q'){}
Queen::~Queen(){}

vector<Move*>Queen::computeValidMoves(const Board& board) const 
{
	vector<Move*> validMoves;

	// forward
	Square* squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getForwardSquare(squareCursor);
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
	// backwards
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getBackwardSquare(squareCursor);
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
	// left
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getLeftSquare(squareCursor);
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
	// right
	squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = board.getRightSquare(squareCursor);
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