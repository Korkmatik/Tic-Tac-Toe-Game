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
	while (!isGameOver && !escape) {
		Draw();
		Input();
		Logic();

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
	Console::set_cursor_position(2, 3);
}

void Game::Input() {
	char choice = (char)_getwch();
	switch (choice) {
	case ESCAPE:
		escape = true;
		break;
	default:
		break;
	}
}

void Game::Logic() {
	
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
	isGameOver = false;
	escape = false;
	Console::clearScreen();
}

