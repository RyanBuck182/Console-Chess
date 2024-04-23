#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
	Pawn(Square*, bool);
	
	std::vector<Move*> computeValidMoves() const override;
	void makeMove(Move* move) override;
private:
	void makeEnPassantMove(Move* move);
	void makePromotionMove(Move* move);

	bool hasMoved;
};

#endif