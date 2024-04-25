#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

class Square;
class Move;
class King;

class Board {
public:
	enum BoardState { WhiteToPlay, BlackToPlay, WhiteWin, BlackWin, Stalemate, Draw };
	
	static const int BOARD_LENGTH = 8;
	static const int BOARD_SIZE = BOARD_LENGTH * BOARD_LENGTH;

	static void initialize();
	static void clear();

	static bool idInRange(int);

	static BoardState getState();
	static void setState(BoardState);
	static Square* getSquareFromId(int);
	static bool isSquareAttacked(int, bool);
	static bool isSquareAttacked(Square*, bool);

	static Square* getNorthSquare(Square*);
	static Square* getSouthSquare(Square*);
	static Square* getEastSquare(Square*);
	static Square* getWestSquare(Square*);
	static Square* getForwardSquare(Square*);
	static Square* getBackwardSquare(Square*);
	static Square* getRightSquare(Square*);
	static Square* getLeftSquare(Square*);

	static Move* getLastMove();
	static std::vector<Move*> getMoveList();
	static bool moveIsValid(Move*);
	static void correctMoveType(Move*);
	static void makeMove(Move*);
	static void calculateAttacks();
	static void updateState();

	static std::string formatAsString();
private:
	enum PieceType { Empty,
		PawnWhite, KnightWhite, BishopWhite, RookWhite, QueenWhite, KingWhite,
		PawnBlack, KnightBlack, BishopBlack, RookBlack, QueenBlack, KingBlack,
	};
	static const PieceType DEFAULT_BOARD[BOARD_SIZE];

	static King* whiteKing;
	static King* blackKing;

	static BoardState state;
	static Square* board[BOARD_SIZE];
	static bool boardWhiteAttacks[BOARD_SIZE];
	static bool boardBlackAttacks[BOARD_SIZE];

	static std::vector<Move*> moveList;
};

#endif