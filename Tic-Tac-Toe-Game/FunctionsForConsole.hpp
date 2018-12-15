#pragma once

namespace Console {
	typedef enum {
		BLUE = 11, WHITE = 7, RED = 12, GREEN_BACKGROUND = 34, GREEN = 2, YELLOW = 6, 
		PURPLE = 5, BLUE_BAKCGROUND = 51
	} COLOR;

	void changeConsoleColor(COLOR color);

	void clearScreen();

	void quit(unsigned sec, unsigned returnCode);

	void set_cursor_position(int x, int y);
}