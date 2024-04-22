#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

class Square;
struct Move;

class Board {
public:
	enum BoardState { WhiteToPlay, BlackToPlay, Win, Stalemate, Draw };
	
	static const int BOARD_LENGTH = 8;
	static const int BOARD_SIZE = BOARD_LENGTH * BOARD_LENGTH;

	static BoardState state;
	static Square* board[BOARD_SIZE];
	static bool boardWhiteAttack[BOARD_SIZE];
	static bool boardBlackAttack[BOARD_SIZE];
	static std::vector<Move*> moveList;

	static void initialize();
	static void clear();

	static bool idInRange(int);
	static Square* getSquareFromId(int);

	static Square* getNorthSquare(Square*);
	static Square* getSouthSquare(Square*);
	static Square* getEastSquare(Square*);
	static Square* getWestSquare(Square*);
	static Square* getForwardSquare(Square*);
	static Square* getBackwardSquare(Square*);
	static Square* getRightSquare(Square*);
	static Square* getLeftSquare(Square*);

	static Move* getLastMove();
	static void makeMove(Move*);

	static std::string formatAsString();
};

#endif