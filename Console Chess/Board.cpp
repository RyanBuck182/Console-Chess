#include <sstream>
#include <cctype>

#include "Board.h"
#include "Square.h"
#include "Move.h"
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

using namespace std;

const Board::PieceType Board::DEFAULT_BOARD[BOARD_SIZE] = {
	RookWhite, KnightWhite, BishopWhite, QueenWhite,  KingWhite, BishopWhite, KnightWhite, RookWhite,
	PawnWhite,   PawnWhite,   PawnWhite,  PawnWhite,  PawnWhite,   PawnWhite,   PawnWhite, PawnWhite,
		Empty,       Empty,       Empty,      Empty,      Empty,       Empty,       Empty,     Empty,
		Empty,       Empty,       Empty,      Empty,      Empty,       Empty,       Empty,     Empty,
		Empty,       Empty,       Empty,      Empty,      Empty,       Empty,       Empty,     Empty,
		Empty,       Empty,       Empty,      Empty,      Empty,       Empty,       Empty,     Empty,
	PawnBlack,   PawnBlack,   PawnBlack,  PawnBlack,  PawnBlack,   PawnBlack,   PawnBlack, PawnBlack,
	RookBlack, KnightBlack, BishopBlack,  QueenBlack, KingBlack, BishopBlack, KnightBlack, RookBlack,
};

bool Board::idInRange(int id) {
	if (id < 0 || id >= BOARD_SIZE)
		return false;
	return true;
}

Board::Board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		Square* square = new Square(this, i);

		bool isWhite = static_cast<int>(DEFAULT_BOARD[i]) <= 6;

		switch (DEFAULT_BOARD[i]) {
			case PawnWhite:
			case PawnBlack:
				square->setPiece(new Pawn(this, square, isWhite));
				break;
			case KnightWhite:
			case KnightBlack:
				square->setPiece(new Knight(this, square, isWhite));
				break;
			case BishopWhite:
			case BishopBlack:
				square->setPiece(new Bishop(this, square, isWhite));
				break;
			case RookWhite:
			case RookBlack:
				square->setPiece(new Rook(this, square, isWhite));
				break;
			case QueenWhite:
			case QueenBlack:
				square->setPiece(new Queen(this, square, isWhite));
				break;
			case KingWhite:
			case KingBlack:
				square->setPiece(new King(this, square, isWhite));
				if (isWhite)
					whiteKing = static_cast<King*>(square->getPiece());
				else
					blackKing = static_cast<King*>(square->getPiece());
				break;
			default:
				break;
		}

		boardSquares[i] = square;
		pieceList.push_back(square->getPiece());
	}

	calculateAttacks();
	state = Board::WhiteToPlay;
}

Board::Board(Board* board) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		boardSquares[i] = new Square(this, board->getSquareFromId(i));
		
		Piece* piece;
		if (boardSquares[i]->isOccupied())
			piece = boardSquares[i]->getPiece()->clone(board, boardSquares[i]);
		else
			piece = nullptr;
		
		if (piece != nullptr)
			pieceList.push_back(piece);

		King* kingPiece = dynamic_cast<King*>(piece);
		if (kingPiece != nullptr)
			if (kingPiece->isWhite())
				whiteKing = kingPiece;
			else
				blackKing = kingPiece;
	}

	vector<Move*> oldMoveList;
	for (int i = 0; i < oldMoveList.size(); i++)
		moveList.push_back(oldMoveList[i]);

	state = board->state;

	calculateAttacks();
}

Board::~Board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		delete boardSquares[i];
		boardSquares[i] = nullptr;
	}

	for (int i = 0; i < pieceList.size(); i++) {
		pieceList[i] = nullptr;
	}
	whiteKing = nullptr;
	blackKing = nullptr;

	for (int i = 0; i < moveList.size(); i++) {
		delete moveList[i];
		moveList[i] = nullptr;
	}
	moveList.clear();
}

Board::BoardState Board::getState() const {
	return state;
}

void Board::setState(Board::BoardState state) {
	Board::state = state;
}

Square* Board::getSquareFromId(int id) const {
	if (!idInRange(id))
		throw "Id not in range.";
	return boardSquares[id];
}

bool Board::isSquareAttacked(int id, bool byWhite) const {
	return (!byWhite) ? boardBlackAttacks[id] : boardWhiteAttacks[id];
}

bool Board::isSquareAttacked(Square* square, bool byWhite) const {
	return (!byWhite) ? boardBlackAttacks[square->getId()] : boardWhiteAttacks[square->getId()];
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
	if (state == WhiteToPlay)
		return getNorthSquare(square);
	else
		return getSouthSquare(square);
}

Square* Board::getBackwardSquare(Square* square) {
	if (state == WhiteToPlay)
		return getSouthSquare(square);
	else
		return getNorthSquare(square);
}

Square* Board::getRightSquare(Square* square) {
	if (state == WhiteToPlay)
		return getEastSquare(square);
	else
		return getWestSquare(square);
}

Square* Board::getLeftSquare(Square* square) {
	if (state == WhiteToPlay)
		return getWestSquare(square);
	else
		return getEastSquare(square);
}

Move* Board::getLastMove() const {
	if (moveList.size() > 0)
		return moveList.back();
	else
		throw "Can not retrieve the last element of an empty move list.";
}

vector<Move*> Board::getMoveList() const {
	return moveList;
}

bool Board::moveIsValid(Move* move) const {
	if (!move->getStartSquare()->isOccupied())
		return false;

	if (state == WhiteToPlay && !move->getStartSquare()->getPiece()->isWhite() || state == BlackToPlay && move->getStartSquare()->getPiece()->isWhite())
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

void Board::correctMoveType(Move* move) const {
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
	move->getStartSquare()->getPiece()->makeMove(move);

	calculateAttacks();
	updateState();
}

void Board::calculateAttacks() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		boardWhiteAttacks[i] = false;
		boardBlackAttacks[i] = false;
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		if (boardSquares[i]->isOccupied()) {
			vector<Square*> attackedSquares = boardSquares[i]->getPiece()->getAttackedSquares();
			for (int j = 0; j < attackedSquares.size(); j++) {
				if (boardSquares[i]->getPiece()->isWhite())
					boardWhiteAttacks[attackedSquares[j]->getId()] = true;
				else
					boardBlackAttacks[attackedSquares[j]->getId()] = true;
			}
		}
	}
}

void Board::updateState() {
	whiteKing->setInCheck(isSquareAttacked(whiteKing->getSquare(), !whiteKing->isWhite()));
	blackKing->setInCheck(isSquareAttacked(blackKing->getSquare(), !blackKing->isWhite()));

	King* king = (state == WhiteToPlay) ? blackKing : whiteKing;

	vector<Square*> adjacentSquares = king->getAttackedSquares();
	bool kingCanMove = false;
	for (int i = 0; i < adjacentSquares.size(); i++) {
		if (!isSquareAttacked(adjacentSquares[i], !king->isWhite())) {
			kingCanMove = true;
			break;
		}
	}

	if (king->inCheck() && !kingCanMove)
		state = (king->isWhite()) ? BlackWin : WhiteWin;
	else if (!kingCanMove)
		state = Stalemate;
	else {
		bool sufficientMaterial = false;
		int threePointPieceCount = 0;

		for (int i = 0; i < BOARD_SIZE; i++) {
			if (!boardSquares[i]->isOccupied())
				continue;

			char pieceSymbol = tolower(boardSquares[i]->getPiece()->getPieceSymbol());
			if (pieceSymbol == 'p' || pieceSymbol == 'r' || pieceSymbol == 'q') {
				sufficientMaterial = true;
				break;
			} else if (threePointPieceCount++ > 1) {
				sufficientMaterial = true;
				break;
			}
		}

		if (!sufficientMaterial)
			state = Draw;
		else
			state = (state == WhiteToPlay) ? BlackToPlay : WhiteToPlay;
	}
}

vector<Piece*> Board::getPieceList() const {
	return pieceList;
}

string Board::formatAsString() {
	stringstream str;

	if (state == WhiteToPlay) {
		str << "  +---+---+---+---+---+---+---+---+\n";
		for (int i = BOARD_LENGTH; i > 0; i--) {
			str << i;
			for (int j = BOARD_LENGTH; j > 0; j--) {
				str << " | ";
				Piece* piece = getSquareFromId(i * BOARD_LENGTH - j)->getPiece();
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
		for (int i = 1; i <= BOARD_LENGTH; i++) {
			str << i;
			for (int j = 1; j <= BOARD_LENGTH; j++) {
				str << " | ";
				Piece* piece = getSquareFromId(i * BOARD_LENGTH - j)->getPiece();
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