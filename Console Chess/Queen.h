#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
	Queen(Board*, Square*, bool);
	Piece* clone(Board*, Square*) const override;

	std::vector<Move*> computeValidMoves() const override;
	std::vector<Square*> getAttackedSquares() const override;
};

#endif