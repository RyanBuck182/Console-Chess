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
	bool getIsOccupied() const;
	Piece* getPiece() const;
	void setPiece(Piece*);

	bool operator==(const Square&);
	friend std::istream& operator>>(std::istream&, Square*&);
private:
	int id;
	bool isOccupied;
	Piece* piece;
};

#endif