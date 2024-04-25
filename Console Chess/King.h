#pragma once
#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
	King(Square*, bool);
	~King();
	std::vector<Move*> computeValidMoves() const override;
};

#endif