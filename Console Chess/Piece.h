#ifndef PIECE_H
#define PIECE_H

#include <vector>

class Square;
class Board;
class Move;

class Piece {
public:
	Piece(Square*, bool, char, char);

	Square* square; //add accessor and mutator
	bool isWhite; //add accessor

	//add accessor
	char whitePieceSymbol;
	char blackPieceSymbol;

	virtual std::vector<Move> computeValidMoves(const Board&) const = 0;
};

#endif