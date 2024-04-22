#ifndef MOVE_H
#define MOVE_H

#include <iostream>

class Square;

struct Move {
	enum MoveType { Standard, Capture, DoublePawn, EnPassant, Castle };

	Move(Square*, Square*);
	Move(Square*, Square*, MoveType);
	~Move();

	Square* startSquare;
	Square* endSquare;
	MoveType moveType;

	bool operator==(const Move& move) const;
	friend std::istream& operator>>(std::istream&, Move*&);
};

#endif