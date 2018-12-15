#pragma once

struct Player {
	int wins;
	char name[50];
	char symbol;
	bool isHisTurn;
};

class Game {
public:
	Game();
	~Game();

	void startGame();
	

private:
#define GAME_WIDTH 14
#define GAME_HEIGHT 9
	char playfield[GAME_HEIGHT][GAME_WIDTH] = {
		"|   |   |   |",
		"|   |   |   |",
		"|___|___|___|",
		"|   |   |   |",
		"|   |   |   |",
		"|___|___|___|",
		"|   |   |   |",
		"|   |   |   |",
		"|   |   |   |"
	};

#define ASCII_ART_WIDTH 58
#define ASCII_ART_HEIGHT 6
	char gameover[ASCII_ART_HEIGHT][ASCII_ART_WIDTH] = {
		"##### ###### ##   ## #####     ##### #      # ##### #####",
		"#     #    # # # # # #         #   # #      # #     #   #",
		"#     #    # #  #  # #         #   #  #    #  #     #####",
		"#  ## ###### #     # ###       #   #  #    #  ###   ##   ",
		"#   # #    # #     # #         #   #   #  #   #     # ## ",
		"##### #    # #     # #####     #####    ##    ##### #   #"
	};

	char drawn[ASCII_ART_HEIGHT][ASCII_ART_WIDTH] = {
		"###   ##### ###### #        # ##    #",
		"#  #  #   # #    # #        # # #   #",
		"#   # ##### #    # #        # #  #  #",
		"#   # ##    ###### #   ##   # #   # #",
		"#  #  # ##  #    # #  #  #  # #    ##",
		"###   #   # #    # ###    ### #     #"
	};

	enum ASCII { W, S, A, D, ENTER = 13, ESCAPE = 27 };

	bool escape = false;
	int cursorX = 2;
	int cursorY = 3;
	int emptyFields = 9;
	int draws = 0;

	Player* turn;
	Player player1 = {};
	Player player2 = {};

	void Setup();
	void Draw();
	void Input();

	void initPlayers(Player& p1, Player& p2);
	void clearPlayfield();
	void printTitle();
	void drawPlayfield();
	void printStats();
	void exitGame();
	void changeCursorY(ASCII a);
	void changeCursorX(ASCII a);
	void submitPosition();
	void checkWin();
	void printWin(const Player & p);
	void printDrawn();
	void printWinner(const Player & p);
	void printAsciiArt(const char str[ASCII_ART_HEIGHT][ASCII_ART_WIDTH]);
	void waitUntilKeyPressed();
	void setCursorToPrintPosition();
	void endGame();
	void chooseRandomStartPlayer(Player & p1, Player & p2);
};

