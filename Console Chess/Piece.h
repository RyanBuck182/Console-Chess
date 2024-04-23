#ifndef PIECE_H
#define PIECE_H

#include <vector>

class Square;
class Board;
struct Move;

class Piece {
public:
	Piece(Square*, bool, char, char);

	Square* getSquare() const;
	void setSquare(Square* square);

	bool isWhite() const;

	char getPieceSymbol() const;

	virtual std::vector<Move*> computeValidMoves() const = 0;
protected:
	Square* square;
	bool pieceIsWhite;
	char whitePieceSymbol;
	char blackPieceSymbol;
};

#endif