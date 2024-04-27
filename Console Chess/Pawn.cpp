#include "Pawn.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "Knight.h"

using namespace std;

Pawn::Pawn(Board* board, Square* square, bool pieceIsWhite) : Piece(board, square, pieceIsWhite, 'P', 'p'), hasMoved(false) {}

vector<Move*> Pawn::computeValidMoves() const {
	vector<Move*> validMoves;
	
	Move* lastMove;

	try {
		lastMove = board->getLastMove();
	} catch (const char*) {
		lastMove = nullptr;
	}
	
	Square* forwardSquare;
	Square* doubleForwardSquare;
	Square* leftDiagonalSquare;
	Square* rightDiagonalSquare;

	//Considering forward
	try {
		forwardSquare = board->getForwardSquare(square);
	} catch (const char*) {
		forwardSquare = nullptr;
	}

	bool forwardSquareIsValid = forwardSquare != nullptr && !forwardSquare->isOccupied();
	if (forwardSquareIsValid)
		validMoves.push_back(new Move(board, square, forwardSquare));

	//Considering forward 2 spaces
	try {
		doubleForwardSquare = board->getForwardSquare(forwardSquare);
	} catch (const char*) {
		doubleForwardSquare = nullptr;
	}

	bool doubleForwardSquareIsValid = doubleForwardSquare != nullptr && !doubleForwardSquare->isOccupied();
	if (forwardSquareIsValid && doubleForwardSquareIsValid && !hasMoved)
		validMoves.push_back(new Move(board, square, doubleForwardSquare, Move::DoublePawn));

	//Considering left diagonal
	try {
		leftDiagonalSquare = board->getLeftSquare(board->getForwardSquare(square));
	} catch (const char*) {
		leftDiagonalSquare = nullptr;
	}

	if (leftDiagonalSquare != nullptr) {
		bool leftDiagonalCaptureIsValid = leftDiagonalSquare->isOccupied() && leftDiagonalSquare->getPiece()->isWhite() != pieceIsWhite;
 		bool leftDiagonalEnPassantIsValid = lastMove != nullptr && lastMove->getMoveType() == Move::DoublePawn && *board->getLeftSquare(square) == *lastMove->getEndSquare();

		if (leftDiagonalCaptureIsValid)
			validMoves.push_back(new Move(board, square, leftDiagonalSquare, Move::Capture));
		else if (leftDiagonalEnPassantIsValid)
			validMoves.push_back(new Move(board, square, leftDiagonalSquare, Move::EnPassant));
	}

	//Considering right diagonal
	try {
		rightDiagonalSquare = board->getRightSquare(board->getForwardSquare(square));
	} catch (const char*) {
		rightDiagonalSquare = nullptr;
	}

	if (rightDiagonalSquare != nullptr) {
		bool rightDiagonalCaptureIsValid = rightDiagonalSquare->isOccupied() && rightDiagonalSquare->getPiece()->isWhite() != pieceIsWhite;
		bool rightDiagonalEnPassantIsValid = lastMove != nullptr && lastMove->getMoveType() == Move::DoublePawn && *board->getRightSquare(square) == *lastMove->getEndSquare();

		if (rightDiagonalCaptureIsValid)
			validMoves.push_back(new Move(board, square, rightDiagonalSquare, Move::Capture));
		else if (rightDiagonalEnPassantIsValid)
			validMoves.push_back(new Move(board, square, rightDiagonalSquare, Move::EnPassant));
	}

	for (int i = 0; i < validMoves.size(); i++) {
		if (validMoves[i]->getEndSquare()->getId() < 8 || validMoves[i]->getEndSquare()->getId() >= 56)
			validMoves[i]->setMoveType(Move::PawnPromotion);
	}

	return validMoves;
}

vector<Square*> Pawn::getAttackedSquares() const {
	vector<Square*> attackedSquares;

	// Right diagonal
	try {
		attackedSquares.push_back(board->getRightSquare(board->getForwardSquare(square)));
	} catch (const char*) {}

	// Left diagonal
	try {
		attackedSquares.push_back(board->getLeftSquare(board->getForwardSquare(square)));
	} catch (const char*) {}

	return attackedSquares;
}

void Pawn::makeMove(Move* move) {
	switch (move->getMoveType()) {
		case Move::EnPassant:
			makeEnPassantMove(move);
			break;
		case Move::PawnPromotion:
			makePromotionMove(move);
			break;
		default:
			makeStandardMove(move);
			break;
	}
}

void Pawn::makeEnPassantMove(Move* move) {
	delete move->getEndSquare()->getPiece();
	move->getEndSquare()->setPiece(move->getStartSquare()->getPiece());
	move->getEndSquare()->getPiece()->setSquare(move->getEndSquare());

	delete board->getBackwardSquare(move->getEndSquare())->getPiece();
	board->getBackwardSquare(move->getEndSquare())->setPiece(nullptr);
	
	move->getStartSquare()->setPiece(nullptr);
}

void Pawn::makePromotionMove(Move* move) {
	cout << "\n";
	cout << " (1) Knight\n";
	cout << " (2) Bishop\n";
	cout << " (3) Rook\n";
	cout << " (4) Queen\n";
	cout << "Choose promotion: ";
	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	Piece* promotedPiece = nullptr;
	switch (choice) {
		case 1:
			promotedPiece = new Knight(board, move->getEndSquare(), move->getStartSquare()->getPiece()->isWhite());
			break;
		case 2:
			promotedPiece = new Bishop(board, move->getEndSquare(), move->getStartSquare()->getPiece()->isWhite());
			break;
		case 3:
			promotedPiece = new Rook(board, move->getEndSquare(), move->getStartSquare()->getPiece()->isWhite());
			break;
		default:
			promotedPiece = new Queen(board, move->getEndSquare(), move->getStartSquare()->getPiece()->isWhite());
			break;
	}

	delete move->getEndSquare()->getPiece();
	move->getEndSquare()->setPiece(promotedPiece);

	move->getStartSquare()->setPiece(nullptr);
}