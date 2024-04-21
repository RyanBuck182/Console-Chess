#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
	Pawn(Square*, bool);

	bool hasMoved;

	std::vector<Move> getValidMoves(const Board&) const override;
};

#endif