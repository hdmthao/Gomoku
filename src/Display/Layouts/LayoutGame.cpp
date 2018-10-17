#include <Display/Layouts/LayoutGame.hpp>
#include <Engine/EngineGlobals.hpp>
#include <Engine/Helpers/Utils.hpp>

LayoutGame::LayoutGame(Game* game, int width, int height):
	Layout(width, height),
	game(game)
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

}
void LayoutGame::windowsExit()
{
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

	refresh();
}
