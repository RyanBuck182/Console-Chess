#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

const int BOARD_SIZE = 64;

class Square;
class Move;

class Board {
public:
	Board();

	bool idInRange(int) const;
	Square* getSquare(int) const;

	Square* board[BOARD_SIZE];
	bool boardWhite[BOARD_SIZE];
	bool boardBlack[BOARD_SIZE];
	bool boardWhiteAttack[BOARD_SIZE];
	bool boardBlackAttack[BOARD_SIZE];

	std::vector<Move> moveList;
};

#endif