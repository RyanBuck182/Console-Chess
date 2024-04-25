#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
	King(Square*, bool);
	
	bool hasMoved() const;
	bool inCheck() const;
	void setInCheck(bool);
	std::vector<Move*> computeValidMoves() const override;
private:
	bool pieceHasMoved;
	bool pieceInCheck;
};

#endif