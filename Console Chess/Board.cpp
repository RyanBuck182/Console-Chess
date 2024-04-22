#include "Board.h"
#include "Square.h"
#include "Move.h"
#include "Piece.h"
#include "Pawn.h"

using namespace std;

Board::Board() {
	for (int i = 0; i < BOARD_SIZE / 4; i++) {
		Square* square = new Square(i);
		square->piece = new Pawn(square, true);
		board[i] = square;
	}

	for (int i = BOARD_SIZE / 4; i < BOARD_SIZE / 4 * 3; i++) {
		Square* square = new Square(i);
		board[i] = square;
	}

	for (int i = BOARD_SIZE / 4 * 3; i < BOARD_SIZE; i++) {
		Square* square = new Square(i);
		square->piece = new Pawn(square, false);
		board[i] = square;
	}

	state = WhiteToPlay;
}

bool Board::idInRange(int id) const {
	if (id < 0 || id >= BOARD_SIZE)
		return false;
	return true;
}

Square* Board::getSquareFromId(int id) const {
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
	if (board.state == Board::WhiteToPlay) {
		out << "  +---+---+---+---+---+---+---+---+\n";
		for (int i = Board::Board::BOARD_LENGTH; i > 0; i--) {
			out << i;
			for (int j = Board::BOARD_LENGTH; j > 0; j--) {
				out << " | ";
				Piece* piece = board.getSquareFromId(i * Board::BOARD_LENGTH - j)->piece;
				if (piece == nullptr)
					out << ' ';
				else
					out << ((piece->isWhite) ? piece->whitePieceSymbol : piece->blackPieceSymbol);
			}
			out << " |\n";
			out << "  +---+---+---+---+---+---+---+---+\n";
		}
		out << "    a   b   c   d   e   f   g   h  \n";
	} else {
		out << "  +---+---+---+---+---+---+---+---+\n";
		for (int i = 1; i <= Board::BOARD_LENGTH; i++) {
			out << i;
			for (int j = 1; j <= Board::BOARD_LENGTH; j++) {
				out << " | ";
				Piece* piece = board.getSquareFromId(i * Board::BOARD_LENGTH - j)->piece;
				if (piece == nullptr)
					out << ' ';
				else
					out << ((piece->isWhite) ? piece->whitePieceSymbol : piece->blackPieceSymbol);
			}
			out << " |\n";
			out << "  +---+---+---+---+---+---+---+---+\n";
		}
		out << "    h   g   f   e   d   c   b   a  \n";
	}
	
	return out;
}