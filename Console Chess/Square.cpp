#include "Square.h"
#include "Piece.h"

Square::Square(int id)
{
	this->id = id;
	this->piece = nullptr;
	isOccupied = false;
}

Square::Square(int id, Piece* piece)
{
	this->id = id;
	this->piece = piece;
	isOccupied = true;
}