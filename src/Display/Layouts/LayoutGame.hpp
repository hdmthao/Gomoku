#ifndef LAYOUTGAME_H_DEFINED
#define LAYOUTGAME_H_DEFINED

#include <Display/Layouts/Layout.hpp>
#include <Game.hpp>

class LayoutGame: public Layout
{
public:
	using Layout::draw;

	LayoutGame(Game* game, int width, int height);
	virtual ~LayoutGame();

	void windowsInit();
	void windowsExit();

	void draw();

private:
	Game* game;

	// Window* info;
};

#endif //LAYOUTGAME_H_DEFINED
