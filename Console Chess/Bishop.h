#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop(Square*, bool);

	std::vector<Move*> computeValidMoves() const override;
};