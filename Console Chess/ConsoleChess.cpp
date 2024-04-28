#include <iostream>
#include <cctype>
#include <string>

#include "ConsoleChess.h"

using namespace std;

int main() {
	bool quitGame = false;
	while (!quitGame) {
		int gameChoice = GameInterface::useGameMenu() - 1;

		enum choices { NewGame, LoadGame, Quit };
		switch (gameChoice) {
			case NewGame:
				GameInterface::board = new Board();
				GameInterface::playGame();
				break;
			case LoadGame:
				GameInterface::loadGame();
				GameInterface::playGame();
				break;
			case Quit:
				cout << '\n';
				quitGame = true;
				break;
			default:
				cout << "Invalid input!\n";
				break;
		}
		cout << endl;
	}

	GameInterface::displayQuitMessage();
}