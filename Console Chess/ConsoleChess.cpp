#include <iostream>
#include <cctype>
#include <string>

#include "ConsoleChess.h"

using namespace std;

int main() {
	bool quitGame = false;
	while (!quitGame) {
		int gameChoice = GameHandler::useGameMenu();
		
		switch (gameChoice) {
			case 1: // New Game
				Board::initialize();

				while (!quitGame && !GameHandler::hasGameEnded()) {
					cout << "\n\n";
					GameHandler::outputBoard();

					int moveChoice = GameHandler::useMoveMenu();

					cout << '\n';
					switch (moveChoice) {
						case 1: { // Make Move
							Move* move = GameHandler::chooseMove();
							Board::makeMove(move);
							break;
						} case 2: // Offer Draw
							GameHandler::offerDraw();
							break;
						case 3: // Resign
							GameHandler::resign();
							break;
						case 4: // Save
							break;
						case 5: // Quit
							quitGame = true;
							break;
						default:
							cout << "Please enter a valid option.\n";
							break;
					}
				}

				GameHandler::displayGameEndMessage();
				break;
			case 2: // Load Game
				break;
			case 3: // Quit
				cout << '\n';
				quitGame = true;
				break;
		}
	}

	GameHandler::displayQuitMessage();
}