#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
	Rook(Square*, bool);

	std::vector<Move*> computeValidMoves() const override;
};

#endif