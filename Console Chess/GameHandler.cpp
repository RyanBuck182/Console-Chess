#include <iostream>
#include <fstream>
#include <vector>
#include "GameHandler.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Board* GameHandler::board = nullptr;

bool GameHandler::currentPlayerIsWhite() {
	return board->getState() == board->WhiteToPlay;
}

int GameHandler::useGameMenu() {
	cout << "Welcome to Console Chess by Ryan Buck and Connor English.\n\n";
	cout << "Please make a selection:\n";
	cout << "  (1) New Game\n";
	cout << "  (2) Load Game\n";
	cout << "  (3) Quit\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return choice;
}

bool GameHandler::hasGameEnded() {
	return board->getState() == board->WhiteWin
		|| board->getState() == board->BlackWin
		|| board->getState() == board->Draw
		|| board->getState() == board->Stalemate;
}

void GameHandler::outputBoard() {
	cout << board->formatAsString();
}

string GameHandler::getSideString(bool current) {
	if (current)
		return (currentPlayerIsWhite()) ? "White" : "Black";
	else
		return (!currentPlayerIsWhite()) ? "White" : "Black";
}

int GameHandler::useMoveMenu() {
	cout << '\n' << getSideString(true) << " To Play\n";
	cout << "  (1) Make move\n";
	cout << "  (2) Offer draw\n";
	cout << "  (3) Resign\n";
	cout << "  (4) Save\n";
	cout << "  (5) Return To Main Menu\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return choice;
}

Move* GameHandler::chooseMove() {
	Move* move = new Move(board);
	bool validMove = false;
	while (!validMove) {
		try {
			cin >> move;
			validMove = true;
		} catch (const char*) {
			validMove = false;
			cout << "Invalid move! Please input a legal move.\n\n";
		}
	}

	return move;
}

void GameHandler::offerDraw() {
	cout << getSideString(true) << " offers a draw.\n";
	cout << "Does " << getSideString(false) << " accept?\n";
	cout << "  (1) Yes\n";
	cout << "  (2) No\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (choice == 1)
		board->setState(board->Draw);
	else
		cout << "Draw declined.\n";
}

void GameHandler::resign() {
	cout << "Are you sure you want to resign?\n";
	cout << "  (1) Yes\n";
	cout << "  (2) No\n";
	cout << "Choice: ";

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (choice == 1)
		board->setState((currentPlayerIsWhite()) ? board->BlackWin : board->WhiteWin);
	else
		cout << "Canceling resignation.\n";
}

void GameHandler::displayGameEndMessage() {
	if (board->getState() == board->WhiteWin || board->getState() == board->BlackWin)
		cout << '\n' << GameHandler::getSideString(GameHandler::currentPlayerIsWhite()) << " Wins!\n\n";
	else if (board->getState() == board->Stalemate)
		cout << "\nThe game has ended in stalemate.\n\n";
	else if (board->getState() == board->Draw)
		cout << "\nThe game has ended in a draw.\n\n";
}

void GameHandler::displayQuitMessage() {
	cout << "Terminating program.\n";
	cout << "Thanks for playing!\n";
}

void GameHandler::saveGame() {
	ofstream saveFile;
	saveFile.open("saved.txt");
	for (int i = 0; i < board->getMoveList().size(); i++)
	{
		saveFile << *board->getMoveList()[i] << endl;
	}
	cout << "Game has been saved!\n";
	saveFile.close();
}

void GameHandler::loadGame() {
	ifstream saveFile;
	saveFile.open("saved.txt");
	
}

