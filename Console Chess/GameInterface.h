/*
Modified By:    Ryan Buck & Connor English
Class:          CSI-240-02
Assignment:     Final Project
Date Assigned:  4/11/24
Due Date:       4/27/24 11:59PM
*/

#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H

#include <string>

class Board;
class Move;

class GameInterface {
public:
	static Board* board;
	static bool currentPlayerIsWhite();
	static int useGameMenu();
	static bool hasGameEnded();
	static void outputBoard();
	static std::string getSideString(bool);
	static void playGame();
	static bool doTurn();
	static int useMoveMenu();
	static Move chooseMove();
	static void offerDraw();
	static void resign();
	static void displayGameEndMessage();
	static void displayQuitMessage();
	static void saveGame();
	static void loadGame();
};

#endif
