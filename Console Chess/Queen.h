#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
	Queen(Board*, Square*, bool);

	std::vector<Move> computeValidMoves() const override;
	std::vector<Square*> getAttackedSquares() const override;
};

#endif