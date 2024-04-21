#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
	Pawn(Square*, bool);

	std::vector<Move> getValidMoves(const Board&) const override;
private:
	bool hasMoved;
};

#endif