#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
	King(Board*, Square*, bool);
	Piece* clone(Board*, Square*) const override;

	bool hasMoved() const;
	bool inCheck() const;
	void setInCheck(bool);
	std::vector<Move*> computeValidMoves() const override;
	std::vector<Square*> getAttackedSquares() const override;
private:
	bool pieceHasMoved;
	bool pieceInCheck;
};

#endif