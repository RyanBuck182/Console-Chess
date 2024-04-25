#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Knight : public Piece {
public:
	Knight(Square*, bool);

	std::vector<Move*> computeValidMoves() const override;
};

#endif