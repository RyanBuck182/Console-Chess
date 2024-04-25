#include <iostream>

#include "GameHandler.h"
#include "Board.h"
#include "Move.h"

using namespace std;

bool GameHandler::currentPlayerIsWhite() {
	return Board::getState() == Board::WhiteToPlay;
}

int GameHandler::useGameMenu() {
	cout << "Welcome to Console Chess by Ryan Buck and Connor English.\n";
	cout << "Please make a selection:\n";
	cout << "  (1) New Game\n";
	cout << "  (2) Load Game\n";
	cout << "  (3) Quit\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	cout << "\n\n";

	return choice;
}

bool GameHandler::hasGameEnded() {
	return Board::getState() == Board::WhiteWin
		|| Board::getState() == Board::BlackWin
		|| Board::getState() == Board::Draw
		|| Board::getState() == Board::Stalemate;
}

void GameHandler::outputBoard() {
	cout << Board::formatAsString();
}

string GameHandler::getSideString(bool current) {
	if (current)
		return (currentPlayerIsWhite()) ? "White" : "Black";
	else
		return (!currentPlayerIsWhite()) ? "Black" : "White";
}

int GameHandler::useMoveMenu() {
	cout << '\n' << getSideString(true) << " To Play\n";
	cout << "  (1) Make move\n";
	cout << "  (2) Offer draw\n";
	cout << "  (3) Resign\n";
	cout << "  (4) Save\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	cout << '\n';

	return choice;
}

Move* GameHandler::chooseMove() {
	Move* move = nullptr;
	while (move == nullptr) {
		cout << "\n";
		try {
			cin >> move;
		} catch (const char*) {
			move = nullptr;
			cout << "Invalid move! Please input a legal move.\n";
		}
	}

	return move;
}

void GameHandler::offerDraw(bool playerOfferingIsWhite) {
	cout << getSideString(playerOfferingIsWhite) << " offers a draw.\n";
	cout << "Does " << getSideString(!playerOfferingIsWhite) << " accept?\n";
	cout << "  (1) Yes";
	cout << "  (2) No";

	int drawChoice;
	cin >> drawChoice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (drawChoice == 1)
		Board::setState(Board::Draw);
	else
		cout << "Draw declined.\n";
}

void GameHandler::resign(bool playerResigningIsWhite) {
	cout << "Are you sure you want to resign?\n";
	cout << "  (1) Yes";
	cout << "  (2) No";

	int resignChoice;
	cin >> resignChoice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (resignChoice == 1)
		Board::setState((Board::getState() == Board::WhiteToPlay) ? Board::BlackWin : Board::WhiteWin);
	else
		cout << "Canceling resignation.\n";
}

void GameHandler::displayGameEndMessage() {
	if (Board::getState() == Board::WhiteWin || Board::getState() == Board::BlackWin)
		cout << GameHandler::getSideString(GameHandler::currentPlayerIsWhite()) << " Wins!\n";
	else if (Board::getState() == Board::Stalemate)
		cout << "The game has ended in stalemate.\n";
	else if (Board::getState() == Board::Draw)
		cout << "The game has ended in a draw.\n";
	else
		cout << "The game has ended.\n";
}

void GameHandler::displayQuitMessage() {
	cout << "Terminating program.\n";
	cout << "Thanks for playing!\n";
}