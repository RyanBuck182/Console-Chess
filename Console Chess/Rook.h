/*
Modified By:    Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
	Rook(Board*, Square*, bool);

	bool hasMoved() const;
	std::vector<Move> computeValidMoves() const override;
	std::vector<Square*> getAttackedSquares() const override;
private:
	bool pieceHasMoved;
};

#endif