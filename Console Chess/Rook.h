#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
class Rook : public Piece 
{
	Rook(Square*, bool);
	~Rook();

	std::vector<Move*> computeValidMoves(const Board&) const override;
};

#endif