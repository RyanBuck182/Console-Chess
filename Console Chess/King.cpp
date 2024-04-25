#include "King.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

King::King(Square* square, bool pieceIsWhite) : Piece(square, pieceIsWhite, 'K', 'k'), pieceHasMoved(false), pieceInCheck(false) {}

bool King::hasMoved() const {
	return pieceHasMoved;
}

bool King::inCheck() const {
	return pieceInCheck;
}

vector<Move*>King::computeValidMoves() const {
	vector<Move*> validMoves;
	vector<Square*> potentialEndSquares;

	// Forward move
	try {
		potentialEndSquares.push_back(Board::getForwardSquare(square));
	} catch (const char*) {}

	// Forward right move
	try {
		potentialEndSquares.push_back(Board::getRightSquare(Board::getForwardSquare(square)));
	} catch (const char*) {}

	// Right move
	try {
		potentialEndSquares.push_back(Board::getRightSquare(square));
	} catch (const char*) {}

	// Right backward move
	try {
		potentialEndSquares.push_back(Board::getBackwardSquare(Board::getRightSquare(square)));
	} catch (const char*) {}

	// Backward move
	try {
		potentialEndSquares.push_back(Board::getBackwardSquare(square));
	} catch (const char*) {}

	// Backward left move
	try {
		potentialEndSquares.push_back(Board::getLeftSquare(Board::getBackwardSquare(square)));
	} catch (const char*) {}

	// Left move
	try {
		potentialEndSquares.push_back(Board::getLeftSquare(square));
	} catch (const char*) {}

	// Left forward move
	try {
		potentialEndSquares.push_back(Board::getForwardSquare(Board::getLeftSquare(square)));
	} catch (const char*) {}

	// Determining valid moves
	for (int i = 0; i < potentialEndSquares.size(); i++) {
		bool squareExists = potentialEndSquares[i];
		bool isUnoccupiedOrCapturable = !potentialEndSquares[i]->isOccupied() || potentialEndSquares[i]->getPiece()->isWhite() != pieceIsWhite;
		bool isAttacked = Board::isSquareAttacked(potentialEndSquares[i], !pieceIsWhite);
	
		if (squareExists && isUnoccupiedOrCapturable && isAttacked)
			validMoves.push_back(new Move(square, potentialEndSquares[i]));
	}

	return validMoves;
}