#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>

class Piece;

class Square {
public:
	Square(int);
	Square(int, Piece*);
	~Square();

	int getId() const;
	Piece* getPiece() const;
	void setPiece(Piece*);

	bool isOccupied() const;

	bool operator==(const Square&);
	friend std::istream& operator>>(std::istream&, Square*&);
private:
	int id;
	Piece* piece;
};

#endif