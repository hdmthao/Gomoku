#include <Display/Layouts/LayoutGame.hpp>
#include <EngineGlobals.hpp>
#include <Helpers/Utils.hpp>

LayoutGame::LayoutGame(Game* game, int width, int height):
	Layout(width, height),
	game(game)
	// info(NULL)
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

	this->game->board->draw(this->main, this->game->currentPlayer);
	this->main->refresh();

	// this->info->refresh();
	refresh();
}
