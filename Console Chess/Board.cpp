#include "Board.h"
#include "Square.h";
#include "Move.h";
#include "Piece.h";

using namespace std;

Board::Board() {
	//implement this

	state = Play;
}

bool Board::idInRange(int id) const {
	if (id < 0 || id >= BOARD_SIZE)
		return false;
	return true;
}

Square* Board::getSquare(int id) const {
	if (!idInRange(id))
		throw "Id not in range.";
	return board[id];
}

void Board::makeMove(Move* move) {
	bool moveIsValid = false;
	vector<Move> validMoves = move->startSquare->piece->computeValidMoves(*this);
	
	for (int i = 0; i < validMoves.size(); i++)
		if (*move == validMoves[i])
			moveIsValid = true;

	if (!moveIsValid)
		return;

	moveList.push_back(*move);

	//check for special moves (castle, en passant, promotion)

	//make move
	move->endSquare->piece = move->startSquare->piece;
	move->endSquare->isOccupied = true;
	
	move->startSquare->piece = nullptr;
	move->startSquare->isOccupied = false;

	//check for win/stalemate/etc
}