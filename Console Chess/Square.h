#ifndef SQUARE_H
#define SQUARE_H
#include "Piece.h"
class Square 
{
public:

	Square();
	Square(Piece*);

	bool isOccupied;
	Piece* piece;
};

#endif