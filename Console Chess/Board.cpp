#include "Board.h"
#include "Square.h"
#include "Move.h"
#include "Piece.h"
#include "Pawn.h"

using namespace std;

Board::Board() {
	for (int i = 0; i < BOARD_SIZE / 4; i++) {
		Square* square = new Square(i);
		square->setPiece(new Pawn(square, true));
		board[i] = square;
	}

	for (int i = BOARD_SIZE / 4; i < BOARD_SIZE / 4 * 3; i++) {
		Square* square = new Square(i);
		board[i] = square;
	}

	for (int i = BOARD_SIZE / 4 * 3; i < BOARD_SIZE; i++) {
		Square* square = new Square(i);
		square->setPiece(new Pawn(square, false));
		board[i] = square;
	}

	state = WhiteToPlay;
}

Board::~Board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		delete board[i];
		board[i] = nullptr;
	}

	for (int i = 0; i < moveList.size(); i++) {
		delete moveList[i];
		moveList[i] = nullptr;
	}
	moveList.clear();
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

Move* Board::getLastMove() const {
	if (moveList.size() > 0)
		return moveList.back();
	else
		throw "Can not retrieve the last element of an empty move list.";
}


void Board::makeMove(Move* move) {
	bool moveIsValid = false;

	if (move->startSquare->piece == nullptr)
		throw "Starting square has no piece on it.";

	vector<Move*> validMoves = move->startSquare->piece->computeValidMoves(*this);
	for (int i = 0; i < validMoves.size(); i++) {
		if (*move == *validMoves[i]) {
			moveIsValid = true;
			move->moveType = validMoves[i]->moveType;
			break;
		}
	}

	if (!moveIsValid)
		throw "That move is not valid.";

	if (state == WhiteToPlay && !move->startSquare->piece->isWhite || state == BlackToPlay && move->startSquare->piece->isWhite)
		throw "Attempting to move other side's piece.";

	moveList.push_back(move);

	//check for special moves (castle, en passant, promotion)

	//make move
	move->endSquare->setPiece(move->startSquare->piece);
	move->endSquare->piece->square = move->endSquare;
	
	move->startSquare->setPiece(nullptr);

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

Square* Board::getNorthSquare(Square* square) const {
	return getSquareFromId(square->id + 8);
}

Square* Board::getSouthSquare(Square* square) const {
	return getSquareFromId(square->id - 8);
}

Square* Board::getEastSquare(Square* square) const {
	return getSquareFromId(square->id + 1);
}

Square* Board::getWestSquare(Square* square) const {
	return getSquareFromId(square->id - 1);
}

Square* Board::getForwardSquare(Square* square) const {
	if (state == WhiteToPlay)
		return getNorthSquare(square);
	else
		return getSouthSquare(square);
}

Square* Board::getBackwardSquare(Square* square) const {
	if (state == WhiteToPlay)
		return getSouthSquare(square);
	else
		return getNorthSquare(square);
}

Square* Board::getRightSquare(Square* square) const {
	if (state == WhiteToPlay)
		return getEastSquare(square);
	else
		return getWestSquare(square);
}

Square* Board::getLeftSquare(Square* square) const {
	if (state == WhiteToPlay)
		return getWestSquare(square);
	else
		return getEastSquare(square);
}