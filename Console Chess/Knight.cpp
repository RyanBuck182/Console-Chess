#include "Knight.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"
using namespace std;

Knight::Knight(Square* square, bool isWhite) : Piece(square, isWhite, 'N', 'n') {}
Knight::~Knight() {}

vector<Move*> Knight::computeValidMoves() const
{
	vector<Move*> validMoves;

	// up up right
	Square* squareCursor = square;
	while (squareCursor != nullptr)
	{
		try {
			squareCursor = Board::getForwardSquare(Board::getForwardSquare(Board::getRightSquare(squareCursor)));
			if (squareCursor->isOccupied())
			{
				if (squareCursor->getPiece()->isWhite() == isWhite())
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
			squareCursor = Board::getForwardSquare(Board::getForwardSquare(Board::getLeftSquare(squareCursor)));
			if (squareCursor->isOccupied())
			{
				if (squareCursor->getPiece()->isWhite() == isWhite())
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
			squareCursor = Board::getRightSquare(Board::getRightSquare(Board::getForwardSquare(squareCursor)));
			if (squareCursor->isOccupied())
			{
				if (squareCursor->getPiece()->isWhite() == isWhite())
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
			squareCursor = Board::getRightSquare(Board::getRightSquare(Board::getBackwardSquare(squareCursor)));
			if (squareCursor->isOccupied())
			{
				if (squareCursor->getPiece()->isWhite() == isWhite())
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
			squareCursor = Board::getBackwardSquare(Board::getBackwardSquare(Board::getLeftSquare(squareCursor)));
			if (squareCursor->isOccupied())
			{
				if (squareCursor->getPiece()->isWhite() == isWhite())
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
			squareCursor = Board::getBackwardSquare(Board::getBackwardSquare(Board::getRightSquare(squareCursor)));
			if (squareCursor->isOccupied())
			{
				if (squareCursor->getPiece()->isWhite() == isWhite())
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
			squareCursor = Board::getLeftSquare(Board::getLeftSquare(Board::getForwardSquare(squareCursor)));
			if (squareCursor->isOccupied())
			{
				if (squareCursor->getPiece()->isWhite() == isWhite())
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
			squareCursor = Board::getLeftSquare(Board::getLeftSquare(Board::getBackwardSquare(squareCursor)));
			if (squareCursor->isOccupied())
			{
				if (squareCursor->getPiece()->isWhite() == isWhite())
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