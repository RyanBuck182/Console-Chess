#include "King.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

King::King(Board* board, Square* square, bool pieceIsWhite) : Piece(board, square, pieceIsWhite, 'K', 'k'), pieceHasMoved(false), pieceInCheck(false) {}

King::~King() {
	board->captureKing(pieceIsWhite);
}

bool King::hasMoved() const {
	return pieceHasMoved;
}

vector<Move*>King::computeValidMoves() const {
	vector<Move*> validMoves;
	vector<Square*> potentialEndSquares = getAttackedSquares();

	// Determining valid moves
	for (int i = 0; i < potentialEndSquares.size(); i++) {
		bool isUnoccupied = !potentialEndSquares[i]->isOccupied();

		if (isUnoccupied) {
			validMoves.push_back(new Move(board, square, potentialEndSquares[i], Move::Standard));
		} else {
			bool isCapturable = potentialEndSquares[i]->getPiece()->isWhite() != pieceIsWhite;
			if (isCapturable)
				validMoves.push_back(new Move(board, square, potentialEndSquares[i], Move::Capture));
		}
	}

	return validMoves;
}

vector<Square*> King::getAttackedSquares() const {
	vector<Square*> attackedSquares;

	// Forward move
	try {
		attackedSquares.push_back(square->getForwardSquare());
	} catch (const char*) {}

	// Forward right move
	try {
		attackedSquares.push_back(square->getForwardSquare()->getRightSquare());
	} catch (const char*) {}

	// Right move
	try {
		attackedSquares.push_back(square->getRightSquare());
	} catch (const char*) {}

	// Right backward move
	try {
		attackedSquares.push_back(square->getRightSquare()->getBackwardSquare());
	} catch (const char*) {}

	// Backward move
	try {
		attackedSquares.push_back(square->getBackwardSquare());
	} catch (const char*) {}

	// Backward left move
	try {
		attackedSquares.push_back(square->getBackwardSquare()->getLeftSquare());
	} catch (const char*) {}

	// Left move
	try {
		attackedSquares.push_back(square->getLeftSquare());
	} catch (const char*) {}

	// Left forward move
	try {
		attackedSquares.push_back(square->getLeftSquare()->getForwardSquare());
	} catch (const char*) {}

	return attackedSquares;
}
