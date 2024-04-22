#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

class Square;
struct Move;

class Board {
public:
	static const int BOARD_LENGTH = 8;
	static const int BOARD_SIZE = BOARD_LENGTH * BOARD_LENGTH;

	enum BoardState { WhiteToPlay, BlackToPlay, Win, Stalemate, Draw };

	Board();
	~Board();

	Square* getNorthSquare(Square*) const;
	Square* getSouthSquare(Square*) const;
	Square* getEastSquare(Square*) const;
	Square* getWestSquare(Square*) const;
	Square* getForwardSquare(Square*) const;
	Square* getBackwardSquare(Square*) const;
	Square* getRightSquare(Square*) const;
	Square* getLeftSquare(Square*) const;

	bool idInRange(int) const;
	Square* getSquareFromId(int) const;
	Move* getLastMove() const;
	void makeMove(Move*);

	friend std::ostream& operator<<(std::ostream&, const Board&);

	Square* board[BOARD_SIZE];
	bool boardWhiteAttack[BOARD_SIZE];
	bool boardBlackAttack[BOARD_SIZE];
	BoardState state;

	std::vector<Move*> moveList;
};

#endif