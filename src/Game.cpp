#include <Game.hpp>
#include <Helpers/Utils.hpp>
#include <Display/Layouts/LayoutGame.hpp>
#include <Input.hpp>
#include <Display/Window.hpp>
#include <EngineGlobals.hpp>
#include <LoadGame.hpp>
#include <vector>
#include <unistd.h>

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
	filename("GOMOKU_"),
	soundX(NULL),
	soundO(NULL),
	soundErr(NULL),
	soundBot(NULL),
	round(0)
{
	bufferX.loadFromFile("/home/himt/cs/cs161/projects/Gomoku/src/Sound/XSound.wav");
	this->soundX = new sf::Sound();
	this->soundX->setBuffer(bufferX);

	bufferO.loadFromFile("/home/himt/cs/cs161/projects/Gomoku/src/Sound/OSound.wav");
	this->soundO = new sf::Sound();
	this->soundO->setBuffer(bufferO);

	bufferErr.loadFromFile("/home/himt/cs/cs161/projects/Gomoku/src/Sound/Error.wav");
	this->soundErr = new sf::Sound();
	this->soundErr->setBuffer(bufferErr);

	bufferBot.loadFromFile("/home/himt/cs/cs161/projects/Gomoku/src/Sound/BotSound.wav");
	this->soundBot = new sf::Sound();
	this->soundBot->setBuffer(bufferBot);

}
Game::~Game()
{
	SAFE_DELETE(this->layout);
	SAFE_DELETE(this->board);
	SAFE_DELETE(this->player1);
	SAFE_DELETE(this->player2);
	SAFE_DELETE(this->pauseMenu);

	this->soundO->stop();
	this->soundO->stop();
	this->soundErr->stop();
	this->soundBot->stop();

	SAFE_DELETE(this->soundX);
	SAFE_DELETE(this->soundO);
	SAFE_DELETE(this->soundErr);
	SAFE_DELETE(this->soundBot);
}
void Game::start(bool isReady, int m_score1, int m_score2, string namePlayer1, string namePlayer2, bool willLoad, bool aiMod)
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
	this->isAi = aiMod;
	this->isQuit = false;
	this->gameOver = false;
	this->gameDraw = false;
	this->isPause = false;
	this->userAskedToSaveGame = false;
	this->countTurn = 0;
	this->round = m_score1 + m_score2 + 1;
	this->captured1 = 0;
	this->captured2 = 0;
	this->layout = new LayoutGame(this, 80, 30);
	this->board = new Board();
	if (willLoad)
	{
		int kindBoard = LoadGame::loadTypeBoard();
		this->isPlay = true;
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
		else
		if (this->isAi) this->currentPlayer = Board::BOT; else this->currentPlayer = Board::PLAYER_2;
		switch (LoadGame::isAiMod)
		{
			case 1:
				this->board->lokiAi->setSize(this->board->height);
				this->board->lokiAi->setBoard(1);
				break;
			case 2:
				this->board->heuristic->setSize(this->board->height);
				this->board->heuristic->setBoard(1);
				break;
			case 3:
				this->board->minimax->setSize(this->board->height);
				this->board->minimax->setBoard(1);
				this->board->minimax->setDepth(4);
				break;
			case 4:
				this->board->mcts->setSize(this->board->height);
				this->board->mcts->setBoard(1);
				break;
			default:
				break;
		}
		EngineGlobals::Game::setGameRule(LoadGame::gameRule);
		EngineGlobals::Board::setXIcon(LoadGame::XIcon);
		EngineGlobals::Board::setOIcon(LoadGame::OIcon);
	}
	else
	{
		this->board->setType(EngineGlobals::Board::style);
		this->board->setBoard(0);
		if (rand() % 2 == 1) this->currentPlayer = Board::PLAYER_1;
		else if (this->isAi) this->currentPlayer = Board::BOT; else this->currentPlayer = Board::PLAYER_2;
		switch (EngineGlobals::Game::AI)
		{
			case 1:
				this->board->lokiAi->setSize(this->board->height);
				this->board->lokiAi->setBoard(0);
				break;
			case 2:
				this->board->heuristic->setSize(this->board->height);
				this->board->heuristic->setBoard(0);
				break;
			case 3:
				this->board->minimax->setSize(this->board->height);
				this->board->minimax->setBoard(0);
				this->board->minimax->setDepth(3);
				break;
			case 4:
				this->board->mcts->setSize(this->board->height);
				this->board->mcts->setBoard(0);
				break;
			default:
				break;
		}
		if (this->isAi) EngineGlobals::Game::setGameRule(1);
	}
	this->player1 = new Player(m_score1, namePlayer1);
	this->player2 = new Player(m_score2, namePlayer2);


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
	if (Input::isPressed(81) || Input::isPressed(113))
	{
		if (this->isPause) this->pause(false); else this->isQuit = true;
	}else
	if (Input::isPressed(27))
	{
		if (this->isPause) this->pause(false); else this->pause(true);
	}else
	if (this->currentPlayer != Board::BOT && (Input::isPressed(KEY_LEFT) || Input::isPressed(65) || Input::isPressed(97)))
	{
		this->board->moveLeft();
	}else
	if (Input::isPressed(KEY_RIGHT) || Input::isPressed(68) || Input::isPressed(100))
	{
		this->board->moveRight();
	}else
	if (Input::isPressed(KEY_UP) || Input::isPressed(87) || Input::isPressed(119))
	{
		this->board->moveUp();
	}else
	if (Input::isPressed(KEY_DOWN) || Input::isPressed(83) || Input::isPressed(115))
	{
		this->board->moveDown();
	} else
	if (Input::isPressed(32))
	{
		if (this->board->update(currentPlayer))
		{
			this->countTurn++;
			if (this->currentPlayer == Board::PLAYER_1)
				this->turnOnSound(1);
			else
				this->turnOnSound(2);
			int directionWin = this->board->isCheckedForWin(this->board->currentX, this->board->currentY);
			if (directionWin != 0)
			{
				this->board->animationWin(directionWin);
				this->gameOver = true;
				return;
			}
			if (EngineGlobals::Game::rule == 5)
			{
				int count = this->board->isCheckCapture(this->board->currentX, this->board->currentY);
				if (this->currentPlayer == Board::PLAYER_1) {
					this->captured1 += count;
					this->countTurn -= 2 * count;
				} else
				{
					this->captured2 += count;
					this->countTurn -= 2 * count;
				}
				if (this->captured1 >= 5 || this->captured2 >= 5)
				{
					this->gameOver = true;
					return;
				}
			}
			if (EngineGlobals::Game::rule == 6)
			{
				if (this->countTurn % 2 == 1) this->swapRole();
			}
			else this->swapRole();
			if (this->countTurn == this->board->height * this->board->width)
			{
				this->gameDraw = true;
			}
		}
		else this->turnOnSound(0);
	} else
	if (Input::isPressed(90) || Input::isPressed(122))
	{
		if (EngineGlobals::Game::rule != 5 && !this->isAi && this->board->undo())
		{
			this->countTurn--;
			if (EngineGlobals::Game::rule == 6)
			{
				if (this->countTurn % 2 == 0) this->swapRole();
			}
			else this->swapRole();
		}
	} else
	if (Input::isPressed(103) || Input::isPressed(71))
	{
		this->swapRole();
		this->gameOver = true;
		return;
	} else
	if (Input::isPressed(77) || Input::isPressed(109))
	{
		EngineGlobals::Game::setSound();
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
				this->start(true, this->player1->getScore(), this->player2->getScore(), this->player1->getName(), this->player2->getName(), false, this->isAi);
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
	if (this->currentPlayer == Board::BOT && this->isPlay)
	{
		this->layout->draw(this->pauseMenu, this->filename, false);
		this->board->makeMove();

		this->countTurn++;
		this->turnOnSound(3);

		int directionWin = this->board->isCheckedForWin(this->board->currentX, this->board->currentY);
		if (directionWin != 0)
		{
			this->board->animationWin(directionWin);
			this->gameOver = true;
			return;
		}
		if (this->countTurn == this->board->height * this->board->width)
		{
			this->gameDraw = true;
		}
		this->swapRole();
		flushinp();
	}
}
void Game::draw()
{
	this->layout->draw(this->pauseMenu, this->filename, false);
}
bool Game::willQuit()
{
	return this->isQuit;
}
bool Game::willDraw()
{
	return this->gameDraw;
}
bool Game::isPlaying()
{
	return this->isPlay;
}
bool Game::willOver()
{
	return this->gameOver;
}
void Game::swapRole()
{
	if (this->currentPlayer == Board::PLAYER_1)
	{
		if (this->isAi)
			this->currentPlayer = Board::BOT;
		else
			this->currentPlayer = Board::PLAYER_2;
	} else
	{
		this->currentPlayer = Board::PLAYER_1;
	}
}
int Game::checkPlayerWin()
{
	if (this->currentPlayer == Board::PLAYER_1)
	{
		return 1;
	}
	else
	if (this->currentPlayer == Board::PLAYER_2)
	{
		return 2;
	}
	else
	{
		return 3;
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
	std::vector<std::string> games = LoadGame::listGames();
	int siz = games.size() + 1;
	if (siz < 9)
	{
		this->filename = this->filename + "0" + (char)(siz + '0');
	}
	else
	{
		this->filename = this->filename + (char)(siz / 10 + '0') + (char)(siz % 10 + '0');
	}
	while (1)
	{
		if (tempFileName != "")
			this->layout->draw(this->pauseMenu, tempFileName, false);
		else
			this->layout->draw(this->pauseMenu, filename, true);
		Input::update(-1);
		if (Input::isPressed(27))
		{
			this->userAskedToSaveGame = false;
			this->filename = "GOMOKU_";
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
		if (c == ' ' || len == 9) continue;
		len++;
		tempFileName = tempFileName + c;
	}
	if (tempFileName != "") this->filename = tempFileName;
	LoadGame::saveGame(this->filename, this->player1->getName(), this->player2->getName(), EngineGlobals::Game::AI, EngineGlobals::Game::rule, this->player1->getScore(), this->player2->getScore(), this->board->getSize(),
lastPlayer, this->board->getLastBoard());
	this->isQuit = true;
}
std::vector< std::pair<int, int> > Game::getLastBoard()
{
	return this->board->getLastBoard();
}
int Game::getSize()
{
	switch (EngineGlobals::Board::style)
	{
		case EngineGlobals::Board::SMALL:
			return 9;
		case EngineGlobals::Board::NORMAL:
			return 13;
		case EngineGlobals::Board::BIG:
			return 19;
		case EngineGlobals::Board::BIGEST:
			return 25;
		case EngineGlobals::Board::TICTACTOE:
			return 3;
		default:
			return 0;
	}
}
void Game::turnOnSound(int cur)
{
	if (!EngineGlobals::Game::turnOnSound) return;
	if (cur == 1)
		this->soundX->play();
	else
	if (cur == 2)
		this->soundO->play();
	else
	if (cur == 3)
		this->soundBot->play();
	else
	if (cur == 0)
		this->soundErr->play();
	usleep(10);
}
