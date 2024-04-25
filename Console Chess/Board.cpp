#include <sstream>

#include "Board.h"
#include "Square.h"
#include "Move.h"
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"

using namespace std;

const Board::PieceType Board::DEFAULT_BOARD[BOARD_SIZE] = {
	RookWhite, KnightWhite, BishopWhite, QueenWhite,  KingWhite, BishopWhite, KnightWhite, RookWhite,
	PawnWhite,   PawnWhite,   PawnWhite,  PawnWhite,  PawnWhite,   PawnWhite,   PawnWhite, PawnWhite,
	       Empty,          Empty,          Empty,         Empty,         Empty,          Empty,          Empty,        Empty,
	       Empty,          Empty,          Empty,         Empty,         Empty,          Empty,          Empty,        Empty,
	       Empty,          Empty,          Empty,         Empty,         Empty,          Empty,          Empty,        Empty,
	       Empty,          Empty,          Empty,         Empty,         Empty,          Empty,          Empty,        Empty,
	PawnBlack,   PawnBlack,   PawnBlack,  PawnBlack,  PawnBlack,   PawnBlack,   PawnBlack, PawnBlack,
	RookBlack, KnightBlack, BishopBlack,  KingBlack, QueenBlack, BishopBlack, KnightBlack, RookBlack,
};

Board::BoardState Board::state;
Square* Board::board[BOARD_SIZE];
bool Board::boardWhiteAttack[BOARD_SIZE];
bool Board::boardBlackAttack[BOARD_SIZE];
std::vector<Move*> Board::moveList;

void Board::initialize() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		Square* square = new Square(i);

		bool isWhite = static_cast<int>(DEFAULT_BOARD[i]) < 6;

		switch (DEFAULT_BOARD[i]) {
			case PawnWhite:
			case PawnBlack:
				square->setPiece(new Pawn(square, isWhite));
				break;
			case KnightWhite:
			case KnightBlack:
				square->setPiece(new Knight(square, isWhite));
				break;
			case BishopWhite:
			case BishopBlack:
				square->setPiece(new Bishop(square, isWhite));
				break;
			case RookWhite:
			case RookBlack:
				square->setPiece(new Rook(square, isWhite));
				break;
			case QueenWhite:
			case QueenBlack:
				square->setPiece(new Queen(square, isWhite));
				break;
			//king here
			default:
				break;
		}

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

Board::BoardState Board::getState() {
	return state;
}

Square* Board::getSquareFromId(int id) {
	if (!idInRange(id))
		throw "Id not in range.";
	return board[id];
}

bool Board::isSquareAttacked(int id) {
	return (state == Board::WhiteToPlay) ? boardBlackAttack[id] : boardWhiteAttack[id];
}

bool Board::isSquareAttacked(Square* square) {
	return (state == Board::WhiteToPlay) ? boardBlackAttack[square->getId()] : boardWhiteAttack[square->getId()];
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
	if (move->getStartSquare()->getPiece() == nullptr)
		return false;

	if (state  == Board::WhiteToPlay && !move->getStartSquare()->getPiece()->isWhite() || state == Board::BlackToPlay && move->getStartSquare()->getPiece()->isWhite())
		return false;

	bool moveIsValid = false;
	vector<Move*> validMoves = move->getStartSquare()->getPiece()->computeValidMoves();
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

	vector<Move*> validMoves = move->getStartSquare()->getPiece()->computeValidMoves();
	for (int i = 0; i < validMoves.size(); i++) {
		if (*move == *validMoves[i]) {
			move->setMoveType(validMoves[i]->getMoveType());
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
	move->getStartSquare()->getPiece()->makeMove(move);
	
	//delete move->getEndSquare()->getPiece();
	//move->getEndSquare()->setPiece(move->getStartSquare()->getPiece());
	//move->getEndSquare()->getPiece()->setSquare(move->getEndSquare());
	//move->getStartSquare()->setPiece(nullptr);

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
					str << piece->getPieceSymbol();
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
					str << piece->getPieceSymbol();
			}
			str << " |\n";
			str << "  +---+---+---+---+---+---+---+---+\n";
		}
		str << "    h   g   f   e   d   c   b   a  \n";
	}

	return str.str();
}