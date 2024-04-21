#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "Move.h"

class Square;
class Board;

class Piece {
public:
	Piece(Square*, bool);

	Square* square; //add accessor and mutator
	bool isWhite; //add accessor

	virtual std::vector<Move> getValidMoves(const Board&) const = 0;
};

#endif