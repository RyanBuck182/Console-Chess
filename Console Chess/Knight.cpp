#include "Knight.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Knight::Knight(Board* board, Square* square, bool pieceIsWhite) : Piece(board, square, pieceIsWhite, 'N', 'n') {}

vector<Move*> Knight::computeValidMoves() const {
	vector<Move*> validMoves;
	vector<Square*> potentialEndSquares = getAttackedSquares();

	// Determining valid moves
	for (int i = 0; i < potentialEndSquares.size(); i++) {
		if (potentialEndSquares[i]->isOccupied()) {
			if (potentialEndSquares[i]->getPiece()->isWhite() != pieceIsWhite)
				validMoves.push_back(new Move(board, square, potentialEndSquares[i], Move::Capture));
		} else
			validMoves.push_back(new Move(board, square, potentialEndSquares[i], Move::Standard));
	}

	return validMoves;
}

vector<Square*> Knight::getAttackedSquares() const {
	vector<Square*> attackedSquares;

	// Forward left
	try {
		attackedSquares.push_back(board->getLeftSquare(board->getForwardSquare(board->getForwardSquare(square))));
	} catch (const char*) {}

	// Forward right
	try {
		attackedSquares.push_back(board->getRightSquare(board->getForwardSquare(board->getForwardSquare(square))));
	} catch (const char*) {}

	// Left forward
	try {
		attackedSquares.push_back(board->getForwardSquare(board->getLeftSquare(board->getLeftSquare(square))));
	} catch (const char*) {}

	// Left backward
	try {
		attackedSquares.push_back(board->getBackwardSquare(board->getLeftSquare(board->getLeftSquare(square))));
	} catch (const char*) {}

	// Right forward
	try {
		attackedSquares.push_back(board->getForwardSquare(board->getRightSquare(board->getRightSquare(square))));
	} catch (const char*) {}

	// Right backward
	try {
		attackedSquares.push_back(board->getBackwardSquare(board->getRightSquare(board->getRightSquare(square))));
	} catch (const char*) {}

	// Backward left
	try {
		attackedSquares.push_back(board->getLeftSquare(board->getBackwardSquare(board->getBackwardSquare(square))));
	} catch (const char*) {}

	// Backward right
	try {
		attackedSquares.push_back(board->getRightSquare(board->getBackwardSquare(board->getBackwardSquare(square))));
	} catch (const char*) {}

	return attackedSquares;
}