#include <Display/Layouts/LayoutGame.hpp>
#include <EngineGlobals.hpp>
#include <Helpers/Utils.hpp>

LayoutGame::LayoutGame(Game* game, int width, int height):
	Layout(width, height),
	game(game),
	info(NULL)
{
	this->windowsInit();
}
LayoutGame::~LayoutGame()
{
	this->windowsExit();
}
void LayoutGame::windowsInit()
{
	Layout::windowsInit();
	this->main->setTitle("Gomoku - PvP Mode");

	this->info = new Window(130, 10, 20, 10);
}
void LayoutGame::windowsExit()
{
	this->info->clear();
	SAFE_DELETE(info);
	this->main->clear(); // clear() as in Window
	this->main->refresh(); // clear() as in Window
	Layout::windowsExit();
}
void LayoutGame::draw()
{
	if (! this->game)
		return;

	this->main->clear();
	this->main->refresh();

	this->info->refresh();
	refresh();
}
