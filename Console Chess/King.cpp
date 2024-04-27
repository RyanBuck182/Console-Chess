#include "King.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

King::King(Board* board, Square* square, bool pieceIsWhite) : Piece(board, square, pieceIsWhite, 'K', 'k'), pieceHasMoved(false), pieceInCheck(false) {}

Piece* King::clone(Board* newBoard, Square* newSquare) const {
	Piece* piece = new King(newBoard, newSquare, pieceIsWhite);
	newSquare->setPiece(piece);
	return piece;
}

bool King::hasMoved() const {
	return pieceHasMoved;
}

bool King::inCheck() const {
	return pieceInCheck;
}

void King::setInCheck(bool pieceInCheck) {
	this->pieceInCheck = pieceInCheck;
}

vector<Move*>King::computeValidMoves() const {
	vector<Move*> validMoves;
	vector<Square*> potentialEndSquares = getAttackedSquares();

	// Determining valid moves
	for (int i = 0; i < potentialEndSquares.size(); i++) {
		bool isUnoccupied = !potentialEndSquares[i]->isOccupied();
		bool isAttacked = board->isSquareAttacked(potentialEndSquares[i], !pieceIsWhite);
	
		if (isUnoccupied) {
			if (!isAttacked)
				validMoves.push_back(new Move(board, square, potentialEndSquares[i], Move::Standard));
		} else {
			bool isCapturable = potentialEndSquares[i]->getPiece()->isWhite() != pieceIsWhite;
			if (isCapturable && !isAttacked)
				validMoves.push_back(new Move(board, square, potentialEndSquares[i], Move::Capture));
		}
	}

	return validMoves;
}

vector<Square*> King::getAttackedSquares() const {
	vector<Square*> attackedSquares;

	// Forward move
	try {
		attackedSquares.push_back(board->getForwardSquare(square));
	} catch (const char*) {}

	// Forward right move
	try {
		attackedSquares.push_back(board->getRightSquare(board->getForwardSquare(square)));
	} catch (const char*) {}

	// Right move
	try {
		attackedSquares.push_back(board->getRightSquare(square));
	} catch (const char*) {}

	// Right backward move
	try {
		attackedSquares.push_back(board->getBackwardSquare(board->getRightSquare(square)));
	} catch (const char*) {}

	// Backward move
	try {
		attackedSquares.push_back(board->getBackwardSquare(square));
	} catch (const char*) {}

	// Backward left move
	try {
		attackedSquares.push_back(board->getLeftSquare(board->getBackwardSquare(square)));
	} catch (const char*) {}

	// Left move
	try {
		attackedSquares.push_back(board->getLeftSquare(square));
	} catch (const char*) {}

	// Left forward move
	try {
		attackedSquares.push_back(board->getForwardSquare(board->getLeftSquare(square)));
	} catch (const char*) {}

	return attackedSquares;
}
