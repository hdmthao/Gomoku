#include <Game.hpp>
#include <Helpers/Utils.hpp>
#include <Display/Layouts/LayoutGame.hpp>
#include <Input.hpp>
#include <Display/Window.hpp>
#include <EngineGlobals.hpp>
#include <iostream>

Game::Game():
	layout(NULL),
	board(NULL),
	player1(NULL),
	player2(NULL)
{
}
Game::~Game()
{
	SAFE_DELETE(this->layout);
	SAFE_DELETE(this->board);
	SAFE_DELETE(this->player1);
	SAFE_DELETE(this->player2);

}
void Game::start(bool isReady, int m_score1, int m_score2)
{
	SAFE_DELETE(this->layout);

	if (isReady)
	{
		this->isPlay = true;
	}
	else
	{
		this->isPlay = false;
	}

	this->isQuit = false;
	this->gameOver = false;

	this->layout = new LayoutGame(this, 80, 30);

	this->board = new Board();
	this->board->setType(EngineGlobals::Board::style);
	this->board->setBoard();

	this->player1 = new Player(m_score1);
	this->player2 = new Player(m_score2);

	this->numberOfGame++;
	if (rand() % 2 == 1) this->currentPlayer = Board::PLAYER_1;
	else this->currentPlayer = Board::PLAYER_2;

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
			int directionWin = this->board->isCheckedForWin(this->board->currentX, this->board->currentY);
			if (directionWin != 0)
			{
				this->board->animationWin(directionWin);
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
bool Game::isPlaying()
{
	return this->isPlay;
}
bool Game::willOver()
{
	return this->gameOver;
}
int Game::checkPlayerWin()
{
	if (this->currentPlayer == Board::PLAYER_1)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}
void Game::updateScore(int score1, int score2)
{
	this->player1->setScore(score1);
	this->player2->setScore(score2);
}
