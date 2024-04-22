#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

const int BOARD_LENGTH = 8;
const int BOARD_SIZE = BOARD_LENGTH * BOARD_LENGTH;

enum BoardState { WhiteToPlay, BlackToPlay, Win, Stalemate, Draw };

class Square;
struct Move;

class Board {
public:
	Board();

	bool idInRange(int) const;
	Square* getSquare(int) const;
	Move getLastMove() const;
	void makeMove(Move*);

	friend std::ostream& operator<<(std::ostream&, const Board&);

	Square* board[BOARD_SIZE];
	bool boardWhiteAttack[BOARD_SIZE];
	bool boardBlackAttack[BOARD_SIZE];
	BoardState state;

	std::vector<Move> moveList;
};

#endif