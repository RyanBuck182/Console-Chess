#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>

class Board;
class Piece;

class Square {
public:
	Square(Board*);
	Square(Board*, int);
	Square(Board*, int, Piece*);
	Square(Board*, Square*);
	~Square();

	Board* getBoard() const;
	int getId() const;
	Piece* getPiece() const;
	void setPiece(Piece*);

	bool isOccupied() const;

	bool operator==(const Square&);
	friend std::istream& operator>>(std::istream&, Square*&);
private:
	Board* board;
	int id;
	Piece* piece;
};

#endif