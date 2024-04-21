#ifndef MOVE_H
#define MOVE_H

class Square;

struct Move {
	Move(Square*, Square*);

	Square* startSquare;
	Square* endSquare;

	bool operator==(const Move& move) const;
};

#endif