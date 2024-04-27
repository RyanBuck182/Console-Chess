#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
	Rook(Board*, Square*, bool);
	Piece* clone(Board*, Square*) const override;

	bool hasMoved() const;
	std::vector<Move*> computeValidMoves() const override;
	std::vector<Square*> getAttackedSquares() const override;
private:
	bool pieceHasMoved;
};

#endif