#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Menu.hpp"
#include "FunctionsForConsole.hpp"


Menu::Menu() {}

Menu::~Menu() {}

void Menu::startMenu() {
	while (true) {
		showMenu();
		unsigned choice = getUserChoice();
		validateInput(choice);
	}
}

void Menu::showMenu() {
	printTitle("Menu");
	
	printLines(menu, SUBMENUS);
}

void Menu::printTitle(const char* title) {
	Console::changeConsoleColor(Console::BLUE);
	std::cout << std::endl << "\t" << title << std::endl;
	for (int i = 0; i < MAX_LEN_STR + 15; ++i)
		std::cout << "_";
	changeConsoleColor(Console::WHITE);
	std::cout << std::endl << std::endl;;
}

void Menu::printLines(const char txt[][MAX_LEN_STR], unsigned lines) {
	for (unsigned i = 0; i < lines; ++i)
		std::cout << "\t" << txt[i] << std::endl;
	std::cout << std::endl;
}

unsigned Menu::getUserChoice() {
	char choice = 0;
	do {
		std::cout << "Your choice: ";
		choice = (char)_getwch();
		std::cout << choice;
	} while (!isValidInput(choice));
	return (choice - '0');
}

bool Menu::isValidInput(const char & choice) {
	bool retVal = false;
	int input = choice - '0';

	if (1 <= input && SUBMENUS >= input)
		retVal = true;
	else
		std::cout << std::endl << "Sorry, invalid input." << std::endl;

	return retVal;
}

void Menu::validateInput(const unsigned& choice) {
	Console::clearScreen();
	switch (choice) {
	case 1:
		game.startGame();
		break;
	case 2:
		showControls();
		break;
	case 3:
		printBye();
		Console::quit(1000, 0);
		break;
	}
}



void Menu::showControls() {
	printTitle("Controls");
	printLines(controls, NUMBER_CONTROLS);
	returnToMenu();
}

void Menu::returnToMenu() {
	std::cout << std::endl << "Press any key to return to menu ..." << std::endl;
	_getwch();
	Console::clearScreen();
}

void Menu::printBye() {
	for (int y = 0; y < BYE_HEIGHT; ++y) {
		for (int x = 0; x < BYE_WIDTH; ++x) {
			if (bye[y][x] == '#')
				Console::changeConsoleColor(Console::BLUE_BAKCGROUND);
			std::cout << bye[y][x];
			if (bye[y][x] == '#')
				Console::changeConsoleColor(Console::WHITE);
		}
		std::cout << std::endl;
	}
}
