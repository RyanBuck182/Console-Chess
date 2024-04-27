#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop(Board*, Square*, bool);
	Piece* clone(Board*, Square*) const override;

	std::vector<Move*> computeValidMoves() const override;
	std::vector<Square*> getAttackedSquares() const override;
};

#endif