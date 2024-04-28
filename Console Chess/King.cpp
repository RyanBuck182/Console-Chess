/*
Modified By:    Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

#include "King.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"
#include "Rook.h"

using namespace std;

King::King(Board* board, Square* square, bool pieceIsWhite) : Piece(board, square, pieceIsWhite, 'K', 'k'), pieceHasMoved(false) {}

King::~King() {
	board->captureKing(pieceIsWhite);
}

bool King::hasMoved() const {
	return pieceHasMoved;
}

vector<Move>King::computeValidMoves() const {
	vector<Move> validMoves;
	vector<Square*> potentialEndSquares = getAttackedSquares();

	// Determining valid moves
	for (int i = 0; i < potentialEndSquares.size(); i++) {
		bool isUnoccupied = !potentialEndSquares[i]->isOccupied();

		if (isUnoccupied) {
			validMoves.push_back(Move(board, square, potentialEndSquares[i], Move::Standard));
		} else {
			bool isCapturable = potentialEndSquares[i]->getPiece()->isWhite() != pieceIsWhite;
			if (isCapturable)
				validMoves.push_back(Move(board, square, potentialEndSquares[i], Move::Capture));
		}
	}

	if (!pieceHasMoved) {
		vector<Piece*> pieceList = board->getPieceList();
		for (int i = 0; i < pieceList.size(); i++) {
			Rook* rook = dynamic_cast<Rook*>(pieceList[i]);
			
			if (rook != nullptr && rook->isWhite() == pieceIsWhite && !rook->hasMoved()) {
				bool isWestRook = rook->getSquare()->getId() < square->getId();
				
				if (isWestRook) {
					if (!square->getWestSquare()->isOccupied()
						&& !square->getWestSquare()->getWestSquare()->isOccupied()
						&& !square->getWestSquare()->getWestSquare()->getWestSquare()->isOccupied()
						) {
						validMoves.push_back(Move(board, square, square->getWestSquare()->getWestSquare(), Move::Castle));
					}
				} else {
					if (!square->getEastSquare()->isOccupied()
						&& !square->getEastSquare()->getEastSquare()->isOccupied()
						) {
						validMoves.push_back(Move(board, square, square->getEastSquare()->getEastSquare(), Move::Castle));
					}
				}
			}
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

void King::makeMove(Move move) {
	switch (move.getMoveType()) {
		case Move::Castle:
			makeCastleMove(move);
			break;
		default:
			makeStandardMove(move);
			break;
	}
}

void King::makeCastleMove(Move move) {
	bool isWestRook = false;
	if (move.getEndSquare()->getId() < square->getId())
		isWestRook = true;

	square->setPiece(nullptr);
	move.getEndSquare()->setPiece(this);
	this->setSquare(move.getEndSquare());
	
	Piece* rook = (isWestRook) ? move.getEndSquare()->getWestSquare()->getWestSquare()->getPiece() : move.getEndSquare()->getEastSquare()->getPiece();
	rook->getSquare()->setPiece(nullptr);
	if (isWestRook) {
		move.getStartSquare()->getWestSquare()->setPiece(rook);
		rook->setSquare(move.getStartSquare()->getWestSquare());
	} else {
		move.getStartSquare()->getEastSquare()->setPiece(rook);
		rook->setSquare(move.getStartSquare()->getEastSquare());
	}

}