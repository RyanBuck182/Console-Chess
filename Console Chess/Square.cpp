#include "Square.h"


Square::Square()
{
	this->piece = nullptr;
	isOccupied = false;
}

Square::Square(Piece* piece)
{
	this->piece = piece;
	isOccupied = true;
}