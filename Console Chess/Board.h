#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

const int BOARD_SIZE = 64;

enum BoardState { WhiteToPlay, BlackToPlay, Win, Stalemate, Draw };

class Square;
class Move;

class Board {
public:
	Board();

	bool idInRange(int) const;
	Square* getSquare(int) const;
	Move getLastMove() const;
	void makeMove(Move*);

	Square* board[BOARD_SIZE];
	bool boardWhite[BOARD_SIZE];
	bool boardBlack[BOARD_SIZE];
	bool boardWhiteAttack[BOARD_SIZE];
	bool boardBlackAttack[BOARD_SIZE];
	BoardState state;

	std::vector<Move> moveList;
};

#endif