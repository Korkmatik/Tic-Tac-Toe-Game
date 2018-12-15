#include <Windows.h>

#include "FunctionsForConsole.hpp"

void Console::changeConsoleColor(Console::COLOR color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Console::clearScreen() {
		system("cls");
}

void Console::quit(unsigned sec, unsigned returnCode) {
	Sleep(sec);
	exit(returnCode);
}

// Set cursor position in console
// see http://www.dreamincode.net/forums/topic/153240-console-cursor-coordinates/ 
void Console::set_cursor_position(int x, int y) {
	//Initialize the coordinates
	COORD coord = { x, y };
	//Set the position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
