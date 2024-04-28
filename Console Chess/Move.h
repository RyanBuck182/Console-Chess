/*
Modified By:    Ryan Buck
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

#ifndef MOVE_H
#define MOVE_H

#include <iostream>

class Square;

class Move {
public:
	enum MoveType { Standard, Capture, DoublePawn, EnPassant, PawnPromotion, Castle };

	Move(Board*);
	Move(Board*, Square*, Square*);
	Move(Board*, Square*, Square*, MoveType);
	~Move();

	Square* getStartSquare() const;
	Square* getEndSquare() const;

	MoveType getMoveType() const;
	void setMoveType(MoveType moveType);

	bool operator==(const Move& move) const;
	friend std::ostream& operator<<(std::ostream&, const Move&);
	friend std::istream& operator>>(std::istream&, Move&);
private:
	Board* board;
	Square* startSquare;
	Square* endSquare;
	MoveType moveType;
};

#endif