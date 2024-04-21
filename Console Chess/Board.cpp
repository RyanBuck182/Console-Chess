#include "Board.h"
#include "Square.h";

Board::Board() {
	//implement this
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