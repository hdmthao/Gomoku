#ifndef GAME_H_DEFINED
#define GAME_H_DEFINED

#include <string>
#include <Board.hpp>

class LayoutGame;

class Game
{
	friend class LayoutGame;

public:
	Game();
	virtual ~Game();

	void start();

	void handleInput();
	void update();
	void draw();

	bool willQuit();
	bool willPlay();
	bool willOver();
	bool isPlay;

protected:
	LayoutGame* layout;

	Board* board;

	bool isQuit;
	bool gameOver;

	Board::role currentPlayer;
};

#endif //GAME_H_DEFINED
