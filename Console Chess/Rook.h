#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
	Rook(Square*, bool);

	bool hasMoved() const;
	std::vector<Move*> computeValidMoves() const override;
private:
	bool pieceHasMoved;
};

#endif