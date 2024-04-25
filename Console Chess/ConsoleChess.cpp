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

				while (!GameHandler::hasGameEnded()) {
					GameHandler::outputBoard();

					int moveChoice = GameHandler::useMoveMenu();

					switch (moveChoice) {
						case 1: { // Make Move
							Move* move = GameHandler::chooseMove();
							Board::makeMove(move);
							break;
						} case 2: // Offer Draw
							GameHandler::offerDraw(GameHandler::currentPlayerIsWhite());
							break;
						case 3: // Resign
							GameHandler::resign(GameHandler::currentPlayerIsWhite());
							break;
						case 4: // Save
							break;
						default:
							cout << "Please enter a valid option.\n";
							break;
					}

					cout << "\n\n";
				}

				GameHandler::displayGameEndMessage();
				break;
			case 2: // Load Game
				break;
			case 3: // Quit
				quitGame = true;
				break;
		}
	}

	GameHandler::displayQuitMessage();
}