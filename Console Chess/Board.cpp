#include "Board.h"
#include "Square.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Board::Board() {
	//implement this

	state = WhiteToPlay;
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

Move Board::getLastMove() const {
	return moveList.back();
}

void Board::makeMove(Move* move) {
	bool moveIsValid = false;

	vector<Move> validMoves = move->startSquare->piece->computeValidMoves(*this);
	for (int i = 0; i < validMoves.size(); i++)
		if (*move == validMoves[i])
			moveIsValid = true;

	if (!moveIsValid)
		return;

	if (state == WhiteToPlay && !move->startSquare->piece->isWhite || state == BlackToPlay && move->startSquare->piece->isWhite)
		return;

	moveList.push_back(*move);

	//check for special moves (castle, en passant, promotion)

	//make move
	move->endSquare->piece = move->startSquare->piece;
	move->endSquare->isOccupied = true;
	
	move->startSquare->piece = nullptr;
	move->startSquare->isOccupied = false;

	state = (state == WhiteToPlay) ? BlackToPlay : WhiteToPlay;

	//check for win/stalemate/etc
}

ostream& operator<<(ostream& out, const Board& board) {
	out << "  +---+---+---+---+---+---+---+---+\n";
	for (int i = 0; i < BOARD_LENGTH; i++) {
		out << i;
		for (int j = 0; j < BOARD_LENGTH; j++) {
			out << " | ";
			Piece* piece = board.getSquare(i * BOARD_LENGTH + j)->piece;
			out << (piece->isWhite) ? piece->whitePieceSymbol : piece->blackPieceSymbol;
		}
		out << " |\n";
	}
	out << "    a   b   c   d   e   f   g   h  \n";
	
	return out;
}