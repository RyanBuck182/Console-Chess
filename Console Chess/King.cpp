#include "King.h"
#include "Square.h"
#include "Board.h"
#include "Move.h"

using namespace std;

King::King(Square* square, bool pieceIsWhite) : Piece(square, pieceIsWhite, 'K', 'k') {}
King::~King(){}
vector<Move*>King::computeValidMoves() const
{
	vector<Move*> validMoves;

	Square* forward;
	Square* right;
	Square* left;
	Square* backward;
	Square* forwardRight;
	Square* forwardLeft;
	Square* backwardRight;
	Square* backwardLeft;
	
	try {
		forward = Board::getForwardSquare(square);
	}
	catch (const char*) {
		forward = nullptr;
	}
	bool forwardSquareIsValid = forward != nullptr && (!forward->isOccupied() || (forward->getPiece()->isWhite() != isWhite())) && !Board::isSquareAttacked(forward);
	if (forwardSquareIsValid)
		validMoves.push_back(new Move(square, forward));

	try {
		backward = Board::getBackwardSquare(square);
	}
	catch (const char*) {
		backward = nullptr;
	}
	bool backWardSquareIsValid = backward != nullptr && (!backward->isOccupied() || (backward->getPiece()->isWhite() != isWhite())) && !Board::isSquareAttacked(backward);
	if (backWardSquareIsValid)
		validMoves.push_back(new Move(square, backward));

	try {
		left = Board::getLeftSquare(square);
	}
	catch (const char*) {
		left = nullptr;
	}
	bool leftSquareIsValid = left != nullptr && (!left->isOccupied() || (left->getPiece()->isWhite() != isWhite())) && !Board::isSquareAttacked(left);
	if (leftSquareIsValid)
		validMoves.push_back(new Move(square, left));

	try {
		right = Board::getRightSquare(square);
	}
	catch (const char*) {
		right = nullptr;
	}
	bool rightSquareIsValid = right != nullptr && (!right->isOccupied() || (right->getPiece()->isWhite() != isWhite())) && !Board::isSquareAttacked(right);
	if (rightSquareIsValid)
		validMoves.push_back(new Move(square, right));

	try {
		forwardLeft = Board::getForwardSquare(Board::getLeftSquare(square));
	}
	catch (const char*) {
		forwardLeft = nullptr;
	}
	bool forwardLeftSquareIsValid = forwardLeft != nullptr && (!forwardLeft->isOccupied() || (forwardLeft->getPiece()->isWhite() != isWhite())) && !Board::isSquareAttacked(forwardLeft);
	if (forwardLeftSquareIsValid)
		validMoves.push_back(new Move(square, forwardLeft));

	try {
		forwardRight = Board::getForwardSquare(Board::getRightSquare(square));
	}
	catch (const char*) {
		forwardRight = nullptr;
	}
	bool forwardRightSquareIsValid = forwardRight != nullptr && (!forwardRight->isOccupied() || (forwardRight->getPiece()->isWhite() != isWhite())) && !Board::isSquareAttacked(forwardRight);
	if (forwardRightSquareIsValid)
		validMoves.push_back(new Move(square, forwardRight));


	try {
		backwardLeft = Board::getBackwardSquare(Board::getLeftSquare(square));
	}
	catch (const char*) {
		backwardLeft = nullptr;
	}
	bool backwardLeftSquareIsValid = backwardLeft != nullptr && (!backwardLeft->isOccupied() || (backwardLeft->getPiece()->isWhite() != isWhite())) && !Board::isSquareAttacked(backwardLeft);
	if (backwardLeftSquareIsValid)
		validMoves.push_back(new Move(square, backwardLeft));

	try {
		backwardRight = Board::getBackwardSquare(Board::getRightSquare(square));
	}
	catch (const char*) {
		backwardRight = nullptr;
	}
	bool backwardRightSquareIsValid = backwardRight != nullptr && (!backwardRight->isOccupied() || (backwardRight->getPiece()->isWhite() != isWhite())) && !Board::isSquareAttacked(backwardRight);
	if (backwardRightSquareIsValid)
		validMoves.push_back(new Move(square, backwardRight));

	return validMoves;

	
}