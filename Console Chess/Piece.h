#ifndef PIECE_H
#define PIECE_H

#include <vector>

class Square;
class Board;
class Move;

class Piece {
public:
	Piece(Square*, bool);

	Square* square; //add accessor and mutator
	bool isWhite; //add accessor

	virtual std::vector<Move> computeValidMoves(const Board&) const = 0;
};

#endif