#include <States/GameStateGame.hpp>
#include <Engine/StateManager.hpp>
#include <Engine/Helpers/Utils.hpp>

#include <Engine/StateManager.hpp>
#include <States/GameStateMainMenu.hpp>

GameStateGame::GameStateGame():
	game(NULL),
	willQuit(false)
{ }
GameStateGame::~GameStateGame()
{ }
void GameStateGame::load()
{
		this->game = new Game();
		this->game->start();
}
void GameStateGame::unload()
{
	SAFE_DELETE(this->game);
}
void GameStateGame::update()
{
	if (this->willQuit)
		StateManager::change(new GameStateMainMenu());

	this->game->handleInput();
	this->game->update();

	if (this->game->willQuit())
		this->willQuit = true;

}
void GameStateGame::draw()
{
	if (! this->willQuit)
		this->game->draw();
}
