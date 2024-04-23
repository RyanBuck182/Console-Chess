#ifndef MOVE_H
#define MOVE_H

#include <iostream>

class Square;

class Move {
public:
	enum MoveType { Standard, Capture, DoublePawn, EnPassant, Castle };

	Move(Square*, Square*);
	Move(Square*, Square*, MoveType);
	~Move();

	Square* getStartSquare() const;
	Square* getEndSquare() const;

	MoveType getMoveType() const;
	void setMoveType(MoveType moveType);

	bool operator==(const Move& move) const;
	friend std::istream& operator>>(std::istream&, Move*&);
private:
	Square* startSquare;
	Square* endSquare;
	MoveType moveType;
};

#endif