#include <iostream>
#include <time.h>
#include <Windows.h>
#include <string.h>

#include "Game.hpp"
#include "FunctionsForConsole.hpp"


Game::Game() {
	srand(unsigned(time(NULL)));
}


Game::~Game() {}

void Game::startGame() {
	Setup();
	while (!escape) {
		Draw();
		Input();

		Sleep(1000 / 5);
	}
	exitGame();
}

void Game::Setup() {
	Console::clearScreen();
	initPlayers(player1, player2);
	clearPlayfield();
}

void Game::Draw() {
	Console::clearScreen();
	printTitle();
	drawPlayfield();
	printStats();
}

void Game::Input() {
	Console::set_cursor_position(cursorX, cursorY);
	switch ((char)_getwch()) {
	case ESCAPE:
		escape = true;
		break;
	case 'w':
		/*fall-through*/
	case 'W':
		changeCursorY(Game::W);
		break;
	case 's':
		/*fall through*/
	case 'S':
		changeCursorY(Game::S);
		break;
	case 'a':
		/*fall-through*/
	case 'A':
		changeCursorX(Game::A);
		break;
	case 'd':
		/*fall-through*/
	case 'D':
		changeCursorX(Game::D);
		break;
	case ENTER:
		submitPosition();
		checkWin();
		break;
	}
}

void Game::initPlayers(Player & p1, Player & p2) {
	p1.symbol = 'X';
	p2.symbol = 'O';
	strcpy_s(p1.name, 50, "Player 1");
	strcpy_s(p2.name, 50, "Player 2");

	if (rand() % 2) {
		p1.isHisTurn = false;
		p2.isHisTurn = true;
		turn = &p2;
	}
	else {
		p1.isHisTurn = true;
		p2.isHisTurn = false;
		turn = &p1;
	}
}

void Game::clearPlayfield() {
	for (int y = 0; y < GAME_HEIGHT; ++y)
		for (int x = 0; x < GAME_WIDTH; ++x)
			if (playfield[y][x] == player1.symbol || playfield[y][x] == player2.symbol) {
				playfield[y][x] = ' ';
			}
}

void Game::printTitle() {
	Console::changeConsoleColor(Console::BLUE);
	std::cout << "Tic-Tac-Toe" << std::endl << std::endl;
	Console::changeConsoleColor(Console::WHITE);
}

void Game::drawPlayfield() {
	for (int i = 0; i < GAME_HEIGHT; ++i) {
		std::cout << playfield[i] << std::endl;
	}
}

void Game::printStats() {
	Console::changeConsoleColor(Console::RED);
	Console::set_cursor_position((GAME_WIDTH + 5), 2);
	std::cout << "Current turn: " << turn->name << " (" << turn->symbol << ")" << std::endl;
	Console::changeConsoleColor(Console::BLUE);
	Console::set_cursor_position((GAME_WIDTH + 5), 4);
	std::cout << "Wins " << player1.name << ": " << player1.wins << std::endl;
	Console::set_cursor_position((GAME_WIDTH + 5), 5);
	std::cout << "Wins " << player2.name << ": " << player2.wins << std::endl;
	Console::changeConsoleColor(Console::WHITE);
}

void Game::exitGame() {
	escape = false;
	Console::clearScreen();
}

void Game::changeCursorY(ASCII a) {
	switch (a) {
	case Game::W:
		if ( 3 < cursorY)
			cursorY -= 3;
		else
			cursorY = 9;
		break;
	case Game::S:
		if (9 > cursorY)
			cursorY += 3;
		else
			cursorY = 3;
		break;
	}
}

void Game::changeCursorX(ASCII a) {
	switch (a) {
	case Game::A:
		if (2 < cursorX)
			cursorX -= 4;
		else
			cursorX = 10;
		break;
	case Game::D:
		if (10 > cursorX)
			cursorX += 4;
		else
			cursorX = 2;
		break;
	}
}

void Game::submitPosition() {
	if (playfield[cursorY - 2][cursorX] == ' ') {
		playfield[cursorY - 2][cursorX] = turn->symbol;
		--emptyFields;
		if (player1.isHisTurn) {
			player1.isHisTurn = false;
			player2.isHisTurn = true;
			turn = &player2;
		}
		else {
			player1.isHisTurn = true;
			player2.isHisTurn = false;
			turn = &player1;
		}
	}
	else {
		Console::changeConsoleColor(Console::RED);
		Console::set_cursor_position(1, (GAME_HEIGHT + 4));
		std::cout << "Unable to place '" << turn->symbol << "'. There is no empty space. Try again." << std::endl;
		Console::changeConsoleColor(Console::WHITE);
		_getwch();
	}
}

void Game::checkWin() {
	//All possible combinations to win
	if (strcmp(playfield[1], "| X | X | X |") == 0 || strcmp(playfield[4], "| X | X | X |") == 0 || strcmp(playfield[7], "| X | X | X |") == 0 /*all horizontal possibilities*/ ||
		playfield[1][2] == 'X' && playfield[4][2] == 'X' && playfield[7][2] == 'X' || playfield[1][6] == 'X' && playfield[4][6] == 'X' && playfield[7][6] == 'X' || playfield[1][10] == 'X' && playfield[4][10] == 'X' && playfield[7][10] == 'X' /*All vertical possibilities*/ ||
		playfield[1][2] == 'X' && playfield[4][6] == 'X' && playfield[7][10] == 'X' || playfield[1][10] == 'X' && playfield[4][6] == 'X' && playfield[7][2] == 'X' /*All diagonal possibilities*/) {
		++(player1.wins);
		Console::clearScreen();
		clearPlayfield();
		emptyFields = 9;
		printWin(player1);
	}
	if (strcmp(playfield[1], "| O | O | O |") == 0 || strcmp(playfield[4], "| O | O | O |") == 0 || strcmp(playfield[7], "| O | O | O |") == 0 /*all horizontal possibilities*/ ||
		playfield[1][2] == 'O' && playfield[4][2] == 'O' && playfield[7][2] == 'O' || playfield[1][6] == 'O' && playfield[4][6] == 'O' && playfield[7][6] == 'O' || playfield[1][10] == 'O' && playfield[4][10] == 'O' && playfield[7][10] == 'O' /*All vertical possibilities*/ ||
		playfield[1][2] == 'O' && playfield[4][6] == 'O' && playfield[7][10] == 'O' || playfield[1][10] == 'O' && playfield[4][6] == 'O' && playfield[7][2] == 'O' /*All diagonal possibilities*/) {
		++(player2.wins);
		Console::clearScreen();
		clearPlayfield();
		emptyFields = 9;
		printWin(player2);
	}
	if (!emptyFields) {
		Console::clearScreen();
		clearPlayfield();
		emptyFields = 9;
		printDrawn();
	}
}

void Game::printWin(const Player & p) {
	printAsciiArt(gameover);
	printWinner(p);
	waitUntilKeyPressed();
}

void Game::printDrawn() {
	printAsciiArt(drawn);
	waitUntilKeyPressed();
}

void Game::printAsciiArt(const char str[ASCII_ART_HEIGHT][ASCII_ART_WIDTH]) {
	
	for (int y = 0; y < ASCII_ART_HEIGHT; ++y) {
		for (int x = 0; x < ASCII_ART_WIDTH; ++x) {
			if (str[y][x] == '#')
				Console::changeConsoleColor(Console::GREEN_BACKGROUND);
			std::cout << str[y][x];
			if (str[y][x] == '#')
				Console::changeConsoleColor(Console::WHITE);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Game::printWinner(const Player & p) {
	if (p.symbol == 'X')
		Console::changeConsoleColor(Console::YELLOW);
	else
		Console::changeConsoleColor(Console::PURPLE);
	std::cout << p.name << " Wins." << std::endl;
	Console::changeConsoleColor(Console::WHITE);
}

void Game::waitUntilKeyPressed() {
	std::cout << "Press any key to start another Game (ESC = return to menu) ..." << std::endl;

	if ((char)_getwch() == Game::ESCAPE)
		escape = true;
}

