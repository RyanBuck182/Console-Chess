#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "Move.h"

class Square;
class Board;

class Piece {
public:
	Piece(Square*, bool);

	Square* square;
	bool isWhite;

	virtual std::vector<Move> getValidMoves(const Board&) const = 0;
};

#endif