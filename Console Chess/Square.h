#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>

class Piece;

class Square {
public:
	Square(int);
	Square(int, Piece*);
	~Square();

	void setPiece(Piece*);

	bool operator==(const Square&);
	friend std::istream& operator>>(std::istream&, Square*&);

	//make private
	int id; //add accessor
	bool isOccupied; //add accessor
	Piece* piece; //add accessor
};

#endif