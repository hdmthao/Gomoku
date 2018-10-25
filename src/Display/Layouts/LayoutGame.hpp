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
	void drawNumberTop(int number, bool isVip=false);
	void drawNumberBot(int number, bool isVip=false);

private:
	Game* game;
	Window* infoTop;
	Window* infoBot;
	Window* scoreBoardTop;
	Window* scoreBoardBot;
};

#endif //LAYOUTGAME_H_DEFINED
