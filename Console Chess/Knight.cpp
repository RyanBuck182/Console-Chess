#include "Knight.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Knight::Knight(Square* square, bool pieceIsWhite) : Piece(square, pieceIsWhite, 'N', 'n') {}

vector<Move*> Knight::computeValidMoves() const {
	vector<Move*> validMoves;
	vector<Square*> potentialEndSquares;

	// Forward left move
	try {
		potentialEndSquares.push_back(Board::getLeftSquare(Board::getForwardSquare(Board::getForwardSquare(square))));
	} catch (const char*) {}

	// Forward right move
	try {
		potentialEndSquares.push_back(Board::getRightSquare(Board::getForwardSquare(Board::getForwardSquare(square))));
	} catch (const char*) {}

	// Left forward move
	try {
		potentialEndSquares.push_back(Board::getForwardSquare(Board::getLeftSquare(Board::getLeftSquare(square))));
	} catch (const char*) {}

	// Left backward move
	try {
		potentialEndSquares.push_back(Board::getBackwardSquare(Board::getLeftSquare(Board::getLeftSquare(square))));
	} catch (const char*) {}

	// Right forward move
	try {
		potentialEndSquares.push_back(Board::getForwardSquare(Board::getRightSquare(Board::getRightSquare(square))));
	} catch (const char*) {}

	// Right backward move
	try {
		potentialEndSquares.push_back(Board::getBackwardSquare(Board::getRightSquare(Board::getRightSquare(square))));
	} catch (const char*) {}

	// Backward left move
	try {
		potentialEndSquares.push_back(Board::getLeftSquare(Board::getBackwardSquare(Board::getBackwardSquare(square))));
	} catch (const char*) {}

	// Backward right move
	try {
		potentialEndSquares.push_back(Board::getRightSquare(Board::getBackwardSquare(Board::getBackwardSquare(square))));
	} catch (const char*) {}

	// Determining valid moves
	for (int i = 0; i < potentialEndSquares.size(); i++) {
		if (potentialEndSquares[i]->isOccupied())
			if (potentialEndSquares[i]->getPiece()->isWhite() != isWhite())
				continue;
			else
				validMoves.push_back(new Move(square, potentialEndSquares[i], Move::Capture));
		else
			validMoves.push_back(new Move(square, potentialEndSquares[i], Move::Standard));
	}

	return validMoves;
}