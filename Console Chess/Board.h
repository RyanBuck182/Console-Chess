#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

class Square;
class Move;
class Piece;
class King;

class Board {
public:
	enum BoardState { WhiteToPlay, BlackToPlay, WhiteWin, BlackWin, Draw };
	
	static const int BOARD_LENGTH = 8;
	static const int BOARD_SIZE = BOARD_LENGTH * BOARD_LENGTH;

	static bool idInRange(int);

	Board();
	~Board();

	BoardState getState() const;
	void setState(BoardState);

	Square* getSquareFromId(int) const;
	bool isSquareAttacked(int, bool) const;
	bool isSquareAttacked(Square*, bool) const;

	Move* getLastMove() const;
	std::vector<Move*> getMoveList() const;
	bool moveIsValid(Move*) const;
	void correctMoveType(Move*) const;
	void makeMove(Move*);
	void calculateAttacks();
	void updateState();

	void captureKing(bool);

	std::vector<Piece*> getPieceList() const;

	std::string formatAsString() const;
private:
	enum PieceType { Empty,
		PawnWhite, KnightWhite, BishopWhite, RookWhite, QueenWhite, KingWhite,
		PawnBlack, KnightBlack, BishopBlack, RookBlack, QueenBlack, KingBlack,
	};
	static const PieceType DEFAULT_BOARD[BOARD_SIZE];

	King* whiteKing;
	King* blackKing;

	BoardState state;
	Square* boardSquares[BOARD_SIZE];
	bool boardWhiteAttacks[BOARD_SIZE];
	bool boardBlackAttacks[BOARD_SIZE];

	std::vector<Piece*> pieceList;
	std::vector<Move*> moveList;
};

#endif