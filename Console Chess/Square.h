#ifndef SQUARE_H
#define SQUARE_H

class Piece;

class Square {
public:
	Square(int);
	Square(int, Piece*);
	~Square();

	void setPiece(Piece*);

	//make private
	int id; //add accessor
	bool isOccupied; //add accessor
	Piece* piece; //add accessor
};

#endif