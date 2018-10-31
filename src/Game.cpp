#include <Game.hpp>
#include <Helpers/Utils.hpp>
#include <Display/Layouts/LayoutGame.hpp>
#include <Input.hpp>
#include <Display/Window.hpp>
#include <EngineGlobals.hpp>
#include <LoadGame.hpp>
#include <ncurses.h>

enum Label_Id
{
	RESUME, RESTART, SAVE, QUIT
};

Game::Game():
	layout(NULL),
	board(NULL),
	pauseMenu(NULL),
	player1(NULL),
	player2(NULL),
	filename("GOMOKU")
{
}
Game::~Game()
{
	SAFE_DELETE(this->layout);
	SAFE_DELETE(this->board);
	SAFE_DELETE(this->player1);
	SAFE_DELETE(this->player2);
	SAFE_DELETE(this->pauseMenu);
}
void Game::start(bool isReady, int m_score1, int m_score2, bool willLoad)
{
	SAFE_DELETE(this->layout);
	SAFE_DELETE(this->board);
	SAFE_DELETE(this->pauseMenu);
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
	this->isPause = false;
	this->userAskedToSaveGame = false;
	this->layout = new LayoutGame(this, 80, 30);

	this->board = new Board();
	if (willLoad)
	{
		int kindBoard = LoadGame::loadTypeBoard();
		switch (kindBoard)
		{
			case 1:
				EngineGlobals::Board::setGameStyle(EngineGlobals::Board::TICTACTOE);
				break;
			case 2:
				EngineGlobals::Board::setGameStyle(EngineGlobals::Board::SMALL);
				break;
			case 3:
				EngineGlobals::Board::setGameStyle(EngineGlobals::Board::NORMAL);
				break;
			case 4:
				EngineGlobals::Board::setGameStyle(EngineGlobals::Board::BIG);
				break;
		}
		this->board->setType(EngineGlobals::Board::style);
		this->board->setBoard(1);
		if (LoadGame::loadLastPlayer() == 1) this->currentPlayer = Board::PLAYER_1;
		else this->currentPlayer = Board::PLAYER_2;
	}
	else
	{
		this->board->setType(EngineGlobals::Board::style);
		this->board->setBoard(0);
		if (rand() % 2 == 1) this->currentPlayer = Board::PLAYER_1;
		else this->currentPlayer = Board::PLAYER_2;
	}
	this->player1 = new Player(m_score1);
	this->player2 = new Player(m_score2);


	this->pauseMenu = new Menu(1,
							   1,
							   this->layout->pause->getW() - 2,
							   this->layout->pause->getH() - 2);

	MenuItem* item;

	item = new MenuItem("Resume", RESUME);
	this->pauseMenu->add(item);

	item = new MenuItem("Restart", RESTART);
	this->pauseMenu->add(item);

	item = new MenuItem("Save And Quit", SAVE);
	this->pauseMenu->add(item);

	item = new MenuItem("Quit Game", QUIT);
	this->pauseMenu->add(item);
}
void Game::handleInput()
{

	if (Input::noKeyPressed())
		return;
	if (Input::isPressed(27))
	{
		this->isQuit = true;
	}
	if (Input::isPressed(80) || Input::isPressed(112))
	{
		if (this->isPause) this->pause(false); else this->pause(true);
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
	if (this->gameOver) return;

	if (this->userAskedToSaveGame)
	{
		this->saveGame();
		return;
	}
	if (this->isPause)
	{
		this->pauseMenu->handleInput();
		if (this->pauseMenu->willQuit())
		{

			switch(this->pauseMenu->currentID())
			{
			case RESUME:
				this->pause(false);
				break;

			case RESTART:
				this->start(true, this->player1->getScore(), this->player2->getScore(), false);
				return;

			case SAVE:
				this->userAskedToSaveGame = true;
				break;

			case QUIT:
				this->isQuit = true;
				break;
			}
			this->pauseMenu->reset();
		}
		return;
	}
}
void Game::draw()
{
	this->layout->draw(this->pauseMenu, this->filename);
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
void Game::pause(bool option)
{
	if (option)
		this->isPause = true;
	else
		this->isPause = false;
}
void Game::saveGame()
{
	int lastPlayer = 0;
	if (this->currentPlayer == Board::PLAYER_1)
		lastPlayer = 1;
	else
		lastPlayer = 2;
	int len = 0;
	std::string tempFileName ="";
	while (1)
	{
		if (tempFileName != "")
			this->layout->draw(this->pauseMenu, tempFileName);
		else
			this->layout->draw(this->pauseMenu, filename);
		Input::update(-1);
		if (Input::isPressed(27))
		{
			this->userAskedToSaveGame = false;
			return;
		}
		if (Input::isPressed('\n')) break;
		if (Input::isPressed(KEY_BACKSPACE)) {
			if (tempFileName.empty()) continue;
			tempFileName.erase(tempFileName.length() - 1, 1);
			len--;
		}
		char c = ' ';
		c = Input::getAlphabet();
		if (c == ' ' || len == 8) continue;
		len++;
		tempFileName = tempFileName + c;
	}
	if (tempFileName != "") this->filename = tempFileName;
	LoadGame::saveGame(this->filename, this->player1->getScore(), this->player2->getScore(), this->board->getSize(),
lastPlayer, this->board->getLastBoard());
	this->isQuit = true;
}
