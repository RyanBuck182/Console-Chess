/*
Modified By:    Ryan Buck
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

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
	~Square();

	Board* getBoard() const;
	int getId() const;
	Piece* getPiece() const;
	void setPiece(Piece*);

	Square* getNorthSquare() const;
	Square* getSouthSquare() const;
	Square* getEastSquare() const;
	Square* getWestSquare() const;
	Square* getForwardSquare() const;
	Square* getBackwardSquare() const;
	Square* getRightSquare() const;
	Square* getLeftSquare() const;

	bool isOccupied() const;

	bool operator==(const Square&);
	friend std::istream& operator>>(std::istream&, Square*&);
private:
	Board* board;
	int id;
	Piece* piece;
};

#endif