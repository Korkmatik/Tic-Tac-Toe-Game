#pragma once

namespace Console {
	typedef enum {
		BLUE = 11, WHITE = 7, RED = 12
	} COLOR;

	void changeConsoleColor(COLOR color);

	void clearScreen();

	void quit(unsigned sec, unsigned returnCode);

	void set_cursor_position(int x, int y);
}