#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
public:
	Knight(Board*, Square*, bool);

	std::vector<Move*> computeValidMoves() const override;
	std::vector<Square*> getAttackedSquares() const override;
};

#endif