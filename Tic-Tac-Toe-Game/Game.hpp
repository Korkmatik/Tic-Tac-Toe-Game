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

	enum ASCII { ESCAPE = 27 };

	bool isGameOver = false;
	bool escape = false;

	Player* turn;
	Player player1 = {};
	Player player2 = {};

	void Setup();
	void Draw();
	void Input();
	void Logic();

	void initPlayers(Player& p1, Player& p2);
	void clearPlayfield();
	void printTitle();
	void drawPlayfield();
	void printStats();
	void exitGame();

};

