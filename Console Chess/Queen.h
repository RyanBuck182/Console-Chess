#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
	Queen(Square*, bool);
	~Queen();

	std::vector<Move*> computeValidMoves() const override;
};

#endif