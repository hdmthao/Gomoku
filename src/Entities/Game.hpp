#ifndef GAME_H_DEFINED
#define GAME_H_DEFINED


#include <vector>


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

protected:
	LayoutGame* layout;

	bool isQuit;
};

#endif //GAME_H_DEFINED
