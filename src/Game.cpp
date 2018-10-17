#include <Game.hpp>
#include <Helpers/Utils.hpp>
#include <Display/Layouts/LayoutGame.hpp>
#include <Input.hpp>


Game::Game():
	layout(NULL)
{ }
Game::~Game()
{
	SAFE_DELETE(this->layout);
}
void Game::start()
{
	SAFE_DELETE(this->layout);

	this->isQuit     = false;

	this->layout = new LayoutGame(this, 80, 24);
}
void Game::handleInput()
{
	if (Input::noKeyPressed())
		return;
	if (Input::isPressed(KEY_F(1)))
	{
		this->isQuit = true;
	}
}
void Game::update()
{
}
void Game::draw()
{
	this->layout->draw();
}
bool Game::willQuit()
{
	return this->isQuit;
}
