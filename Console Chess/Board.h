#pragma once
#include <iostream>
#include "Square.h"

using namespace std;
class Board
{
public:
	const int BOARD_SIZE = 64;
	Square* board;
	bool boardWhite[64];
	bool boardBlack[64];
	bool boardWhiteAttack[64];
	bool boardBlackAttack[64];
};