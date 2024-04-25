#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H

#include <string>

class Board;
class Move;

class GameHandler {
public:
	static bool currentPlayerIsWhite();
	static int useGameMenu();
	static bool hasGameEnded();
	static void outputBoard();
	static std::string getSideString(bool);
	static int useMoveMenu();
	static Move* chooseMove();
	static void offerDraw();
	static void resign();
	static void displayGameEndMessage();
	static void displayQuitMessage();
	static void saveGame();
};

#endif
