/*
Modified By:    Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
	King(Board*, Square*, bool);
	~King();

	bool hasMoved() const;
	std::vector<Move> computeValidMoves() const override;
	std::vector<Square*> getAttackedSquares() const override;
	void makeMove(Move move) override;
private:
	void makeCastleMove(Move move);

	bool pieceHasMoved;
};

#endif