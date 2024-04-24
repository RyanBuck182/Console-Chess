#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(Square*, bool);
	~Knight();
	std::vector<Move*> computeValidMoves() const override;
};