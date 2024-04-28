/*
Modified By:    Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

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