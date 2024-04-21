#ifndef SQUARE_H
#define SQUARE_H

class Piece;

class Square {
public:
	Square(int);
	Square(int, Piece*);

	int id;
	bool isOccupied;
	Piece* piece;
};

#endif