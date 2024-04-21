#ifndef MOVE_H
#define MOVE_H

enum MoveType { Standard, Capture, DoublePawn, EnPassant, Castle };

class Square;

struct Move {
	Move(Square*, Square*);
	Move(Square*, Square*, MoveType);

	Square* startSquare;
	Square* endSquare;
	MoveType moveType;

	bool operator==(const Move& move) const;
};

#endif