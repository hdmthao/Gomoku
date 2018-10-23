#include <Game.hpp>
#include <Helpers/Utils.hpp>
#include <Display/Layouts/LayoutGame.hpp>
#include <Input.hpp>
#include <Display/Window.hpp>
#include <EngineGlobals.hpp>

Game::Game():
	layout(NULL),
	board(NULL)
{ }
Game::~Game()
{
	SAFE_DELETE(this->layout);
	SAFE_DELETE(this->board);
}
void Game::start()
{
	SAFE_DELETE(this->layout);

	this->isPlay = false;
	this->isQuit = false;
	this->gameOver = false;

	this->layout = new LayoutGame(this, 80, 30);

	this->board = new Board();
	this->board->setType(EngineGlobals::Board::style);
	this->board->setBoard();

	this->currentPlayer = Board::PLAYER_1;
}
void Game::handleInput()
{
	if (Input::noKeyPressed())
		return;
	if (Input::isPressed(27))
	{
		this->isQuit = true;
	}
	if (Input::isPressed(KEY_LEFT))
	{
		this->board->moveLeft();
	}
	if (Input::isPressed(KEY_RIGHT))
	{
		this->board->moveRight();
	}
	if (Input::isPressed(KEY_UP))
	{
		this->board->moveUp();
	}
	if (Input::isPressed(KEY_DOWN))
	{
		this->board->moveDown();
	}
	if (Input::isPressed(32))
	{
		if (this->board->update(currentPlayer))
		{
			if (this->board->isCheckedForWin())
			{
				this->gameOver = true;
				return;
			}
			if (this->currentPlayer == Board::PLAYER_1)
			{
				this->currentPlayer = Board::PLAYER_2;
			} else
			{
				this->currentPlayer = Board::PLAYER_1;
			}
		}
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
bool Game::willPlay()
{
	return this->isPlay;
}
bool Game::willOver()
{
	return this->gameOver;
}
