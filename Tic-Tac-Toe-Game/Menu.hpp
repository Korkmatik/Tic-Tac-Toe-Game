#pragma once
#include "Game.hpp"

class Menu {
public:
	Menu();
	~Menu();

	void startMenu();

private:
#define SUBMENUS 3
#define MAX_LEN_STR 20
	char menu[SUBMENUS][MAX_LEN_STR] = {
		"1 - Start Game",
		"2 - Controls",
		"3 - Quit"
	};

#define NUMBER_CONTROLS 6
	char controls[NUMBER_CONTROLS][MAX_LEN_STR] = {
		"W\tMove curosor up",
		"A\tMove cursor left",
		"S\tMove cursor down",
		"D\tMove cursor right",
		"ENTER\tPlace X/O",
		"ESC\tReturn to menu"
	};

#define BYE_WIDTH 21
#define BYE_HEIGHT 5
	char bye[ASCII_ART_HEIGHT][BYE_WIDTH] = {
	" ####   #    # #####",
	" #   #   #  #  #    ",
	" ####     ##   #### ",
	" #   #    ##   #    ",
	" ####     ##   #####"
	};

	Game game;

	void showMenu();
	void printTitle(const char* title);
	void printLines(const char txt[][MAX_LEN_STR], unsigned lines);
	unsigned getUserChoice();
	bool isValidInput(const char& choice);
	void validateInput(const unsigned& choice);	
	void showControls();
	void returnToMenu();
	void printBye();
};

