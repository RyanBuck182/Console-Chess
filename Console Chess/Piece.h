/*
Modified By:    Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

#ifndef PIECE_H
#define PIECE_H

#include <vector>

class Square;
class Board;
class Move;

class Piece {
public:
	Piece(Board*, Square*, bool, char, char);
	virtual ~Piece();

	Square* getSquare() const;
	void setSquare(Square* square);

	bool isWhite() const;

	char getPieceSymbol() const;

	virtual std::vector<Move> computeValidMoves() const = 0;
	virtual std::vector<Square*> getAttackedSquares() const = 0;
	virtual void makeMove(Move move);
protected:
	void makeStandardMove(Move move);

	Board* board;
	Square* square;
	bool pieceIsWhite;
	char whitePieceSymbol;
	char blackPieceSymbol;
};

#endif