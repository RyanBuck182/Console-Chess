#include "Square.h"
#include "Piece.h"
#include "Board.h"

using namespace std;

Square::Square(Board* board) {
	this->board = board;
	this->id = -1;
	piece = nullptr;
}

Square::Square(Board* board, int id)
{
	this->board = board;
	this->id = id;
	piece = nullptr;
}

Square::Square(Board* board, int id, Piece* piece)
{
	this->board = board;
	this->id = id;
	setPiece(piece);
}

Square::~Square() {
	if (piece != nullptr) {
		delete piece;
		piece = nullptr;
	}
}

Board* Square::getBoard() const {
	return board;
}

int Square::getId() const {
	return id;
}

Piece* Square::getPiece() const {
	return piece;
}

void Square::setPiece(Piece* piece) {
	this->piece = piece;
}

Square* Square::getNorthSquare() const {
	return board->getSquareFromId(id + 8);
}

Square* Square::getSouthSquare() const {
	return board->getSquareFromId(id - 8);
}

Square* Square::getEastSquare() const {
	return board->getSquareFromId(id + 1);
}

Square* Square::getWestSquare() const {
	return board->getSquareFromId(id - 1);
}

Square* Square::getForwardSquare() const {
	if (board->getState() == Board::WhiteToPlay)
		return getNorthSquare();
	else
		return getSouthSquare();
}

Square* Square::getBackwardSquare() const {
	if (board->getState() == Board::WhiteToPlay)
		return getSouthSquare();
	else
		return getNorthSquare();
}

Square* Square::getRightSquare() const {
	if (board->getState() == Board::WhiteToPlay)
		return getEastSquare();
	else
		return getWestSquare();
}

Square* Square::getLeftSquare() const {
	if (board->getState() == Board::WhiteToPlay)
		return getWestSquare();
	else
		return getEastSquare();
}

bool Square::isOccupied() const {
	return piece != nullptr;
}

bool Square::operator==(const Square& square) {
	return id == square.id;
}

istream& operator>>(istream& in, Square*& square) {
	char column;
	int row;

	cin >> column;
	cin >> row;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	int id = (row - 1) * Board::BOARD_LENGTH + (static_cast<int>(tolower(column) - static_cast<int>('a')));

	square = square->getBoard()->getSquareFromId(id);

	return in;
}