#ifndef GAME_H_DEFINED
#define GAME_H_DEFINED

#include <string>

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
	bool isPlay;

protected:
	LayoutGame* layout;

	bool isQuit;
};

#endif //GAME_H_DEFINED
