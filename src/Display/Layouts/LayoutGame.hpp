#ifndef LAYOUTGAME_H_DEFINED
#define LAYOUTGAME_H_DEFINED

#include <Display/Layouts/Layout.hpp>
#include <Display/Menu.hpp>
#include <Game.hpp>
#include <string>

class LayoutGame: public Layout
{
public:
	using Layout::draw;

	LayoutGame(Game* game, int width, int height);
	virtual ~LayoutGame();

	void windowsInit();
	void windowsExit();

	void draw(Menu* menu, std::string filename, bool isDefault=false);
	void drawNumberTop(int number, bool isVip=false);
	void drawNumberBot(int number, bool isVip=false);

private:
	Game* game;
	Window* infoTop;
	Window* infoBot;
	Window* scoreBoardTop;
	Window* scoreBoardBot;
	Window* help;
	
public:
	Window* pause;
};

#endif //LAYOUTGAME_H_DEFINED
