#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "Move.h"

class Piece {
public:
	int currentSquare;
	bool isWhite;

	virtual vector<Move> getValidMoves(bool boardWhite[], bool boardBlack[]) = 0;
};

#endif