#include <sstream>

#include "Board.h"
#include "Square.h"
#include "Move.h"
#include "Piece.h"
#include "Pawn.h"

using namespace std;

Board::BoardState Board::state;
Square* Board::board[BOARD_SIZE];
bool Board::boardWhiteAttack[BOARD_SIZE];
bool Board::boardBlackAttack[BOARD_SIZE];
std::vector<Move*> Board::moveList;

void Board::initialize() {
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

	state = Board::WhiteToPlay;
}

void Board::clear() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		delete board[i];
		board[i] = nullptr;
	}

	for (int i = 0; i < moveList.size(); i++) {
		delete moveList[i];
		moveList[i] = nullptr;
	}
	moveList.clear();

	initialize();
}

bool Board::idInRange(int id) {
	if (id < 0 || id >= BOARD_SIZE)
		return false;
	return true;
}

Square* Board::getSquareFromId(int id) {
	if (!idInRange(id))
		throw "Id not in range.";
	return board[id];
}

Square* Board::getNorthSquare(Square* square) {
	return Board::getSquareFromId(square->getId() + 8);
}

Square* Board::getSouthSquare(Square* square) {
	return Board::getSquareFromId(square->getId() - 8);
}

Square* Board::getEastSquare(Square* square) {
	return Board::getSquareFromId(square->getId() + 1);
}

Square* Board::getWestSquare(Square* square) {
	return Board::getSquareFromId(square->getId() - 1);
}

Square* Board::getForwardSquare(Square* square) {
	if (state == Board::WhiteToPlay)
		return getNorthSquare(square);
	else
		return getSouthSquare(square);
}

Square* Board::getBackwardSquare(Square* square) {
	if (state == Board::WhiteToPlay)
		return getSouthSquare(square);
	else
		return getNorthSquare(square);
}

Square* Board::getRightSquare(Square* square) {
	if (state == Board::WhiteToPlay)
		return getEastSquare(square);
	else
		return getWestSquare(square);
}

Square* Board::getLeftSquare(Square* square) {
	if (state == Board::WhiteToPlay)
		return getWestSquare(square);
	else
		return getEastSquare(square);
}

Move* Board::getLastMove() {
	if (moveList.size() > 0)
		return moveList.back();
	else
		throw "Can not retrieve the last element of an empty move list.";
}

bool Board::moveIsValid(Move* move) {
	if (move->startSquare->getPiece() == nullptr)
		return false;

	if (state == Board::WhiteToPlay && !move->startSquare->getPiece()->isWhite || state == Board::BlackToPlay && move->startSquare->getPiece()->isWhite)
		return false;

	bool moveIsValid = false;
	vector<Move*> validMoves = move->startSquare->getPiece()->computeValidMoves();
	for (int i = 0; i < validMoves.size(); i++) {
		if (*move == *validMoves[i]) {
			moveIsValid = true;
			break;
		}
	}

	return moveIsValid;
}

void Board::correctMoveType(Move* move) {
	if (!moveIsValid(move))
		throw "Cannot correct the move type of an invalid move.";

	vector<Move*> validMoves = move->startSquare->getPiece()->computeValidMoves();
	for (int i = 0; i < validMoves.size(); i++) {
		if (*move == *validMoves[i]) {
			move->moveType = validMoves[i]->moveType;
			break;
		}
	}
}

void Board::makeMove(Move* move) {
	if (!moveIsValid(move))
		throw "Cannot make an invalid move.";

	correctMoveType(move);

	moveList.push_back(move);

	//check for special moves (castle, en passant, promotion)

	//make move
	delete move->endSquare->getPiece();
	move->endSquare->setPiece(move->startSquare->getPiece());
	move->endSquare->getPiece()->square = move->endSquare;
	move->startSquare->setPiece(nullptr);

	state = (state == Board::WhiteToPlay) ? Board::BlackToPlay : Board::WhiteToPlay;

	//check for win/stalemate/etc
}

string Board::formatAsString() {
	stringstream str;

	if (state == Board::WhiteToPlay) {
		str << "  +---+---+---+---+---+---+---+---+\n";
		for (int i = Board::BOARD_LENGTH; i > 0; i--) {
			str << i;
			for (int j = Board::BOARD_LENGTH; j > 0; j--) {
				str << " | ";
				Piece* piece = Board::getSquareFromId(i * Board::BOARD_LENGTH - j)->getPiece();
				if (piece == nullptr)
					str << ' ';
				else
					str << ((piece->isWhite) ? piece->whitePieceSymbol : piece->blackPieceSymbol);
			}
			str << " |\n";
			str << "  +---+---+---+---+---+---+---+---+\n";
		}
		str << "    a   b   c   d   e   f   g   h  \n";
	} else {
		str << "  +---+---+---+---+---+---+---+---+\n";
		for (int i = 1; i <= Board::BOARD_LENGTH; i++) {
			str << i;
			for (int j = 1; j <= Board::BOARD_LENGTH; j++) {
				str << " | ";
				Piece* piece = Board::getSquareFromId(i * Board::BOARD_LENGTH - j)->getPiece();
				if (piece == nullptr)
					str << ' ';
				else
					str << ((piece->isWhite) ? piece->whitePieceSymbol : piece->blackPieceSymbol);
			}
			str << " |\n";
			str << "  +---+---+---+---+---+---+---+---+\n";
		}
		str << "    h   g   f   e   d   c   b   a  \n";
	}

	return str.str();
}