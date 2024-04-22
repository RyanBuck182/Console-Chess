#pragma once

#include "Piece.h"
class Rook : public Piece 
{
	Rook(Square*, bool);
	~Rook();

	std::vector<Move*> computeValidMoves(const Board&) const override;
};