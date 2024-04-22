#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
	Pawn(Square*, bool);
	~Pawn();

	std::vector<Move*> computeValidMoves(const Board&) const override;
private:
	bool hasMoved;
};

#endif