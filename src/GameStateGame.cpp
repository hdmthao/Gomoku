#include <GameStateGame.hpp>
#include <StateManager.hpp>
#include <Helpers/Utils.hpp>
#include <Input.hpp>
#include <Display/Window.hpp>
#include <StateManager.hpp>
#include <GameStateMainMenu.hpp>
#include <LoadGame.hpp>
#include <LoadStat.hpp>
#include <iostream>
#include <SFML/Audio.hpp>

GameStateGame::GameStateGame(bool aiMod):
	game(NULL),
	willQuit(false),
	isReady(false),
	filename("Gomoku_"),
	countGame(0),
	sound(NULL),
	soundWin(NULL),
	soundDraw(NULL),
	soundLose(NULL)
{
	LoadGame::loadStatictis();
	if (EngineGlobals::Game::currentGame == "")
	{
		this->score1 = 0;
		this->score2 = 0;
		this->namePlayer1 = EngineGlobals::Game::namePlayer1;
		this->namePlayer2 = EngineGlobals::Game::namePlayer2;
		if (!aiMod){
			for (unsigned int i = 1; i <= 16; ++i)
			{
				if (LoadGame::name[i] == this->namePlayer1) LoadGame::count[i]++;
				if (LoadGame::name[i] == this->namePlayer2) LoadGame::count[i]++;
			}
		}
		this->isAi = EngineGlobals::Game::AI;
	}
	else
	{
		LoadGame::load(EngineGlobals::Game::currentGame);
		this->score1 = LoadGame::loadScore(1);
		this->score2 = LoadGame::loadScore(2);
		this->namePlayer1 = LoadGame::loadName(1);
		this->namePlayer2 = LoadGame::loadName(2);
		this->isAi = LoadGame::isAiMod;

	}
	this->tmpXIcon = EngineGlobals::Board::XIcon;
	this->tmpOIcon = EngineGlobals::Board::OIcon;
	this->tmpRule = EngineGlobals::Game::rule;

	this->currentWin = 0;
	this->sound = new sf::Music();

	this->sound->openFromFile("/home/himt/cs/cs161/projects/Gomoku/src/Sound/Game.wav");
	this->sound->setLoop(true);

	this->soundWin = new sf::Music();
	this->soundWin->openFromFile("/home/himt/cs/cs161/projects/Gomoku/src/Sound/GameWin.wav");

	this->soundDraw = new sf::Music();
	this->soundDraw->openFromFile("/home/himt/cs/cs161/projects/Gomoku/src/Sound/GameDraw.wav");

	this->soundLose = new sf::Music();
	this->soundLose->openFromFile("/home/himt/cs/cs161/projects/Gomoku/src/Sound/GameLose.wav");

}
GameStateGame::~GameStateGame()
{
	LoadGame::saveStatictis();
	if (this->countGame > 0 && EngineGlobals::Game::currentGame == "") saveHistory();
	vecScore.clear();
	vecBoard.clear();
	SAFE_DELETE(this->sound);
	SAFE_DELETE(this->soundWin);
	SAFE_DELETE(this->soundDraw);
	SAFE_DELETE(this->soundLose);
}
void GameStateGame::load()
{

	this->game = new Game();
	if (!this->isReady && EngineGlobals::Game::currentGame != "")
	{
		this->game->start(this->isReady, this->score1, this->score2, this->namePlayer1, this->namePlayer2, 1, this->isAi);
		this->isReady = true;
	}
	else
		this->game->start(this->isReady, this->score1, this->score2, this->namePlayer1, this->namePlayer2, 0, this->isAi);
}
void GameStateGame::unload()
{
	SAFE_DELETE(this->game);
	SAFE_DELETE(this->sound);
	SAFE_DELETE(this->soundWin);
	SAFE_DELETE(this->soundDraw);
	EngineGlobals::Board::setXIcon(this->tmpXIcon);
	EngineGlobals::Board::setOIcon(this->tmpOIcon);
	EngineGlobals::Game::setGameRule(this->tmpRule);
}
void GameStateGame::update()
{
	if (this->willQuit)
		StateManager::change(new GameStateMainMenu());

	this->game->handleInput();
	this->game->update();
	if (!this->isReady)
	{
		this->game->draw();
		GameStateGame::showDialog("Are You Ready???", 25, 6);
	}
	if (this->game->willOver())
	{
		this->currentWin = this->game->checkPlayerWin();
		if (this->currentWin == 1)
		{
			this->score1++;
			this->vecScore.push_back(std::make_pair(this->score1, this->score2));
			if (this->isAi) LoadGame::winGame++;
		}
		else
		{
			this->score2++;
			this->vecScore.push_back(std::make_pair(this->score1, this->score2));
		}
		this->game->updateScore(this->score1, this->score2);
		this->game->draw();
		if (this->isAi) LoadGame::playedGameCamp++; else LoadGame::playedGameMul++;
		this->countGame++;
		this->vecBoard.push_back(this->game->getLastBoard());
		if (EngineGlobals::Game::turnOnSound)
		{
			if (this->currentWin == 3)
				this->soundLose->play();
			else
				this->soundWin->play();
		}
		Input::update(6000);
		if (EngineGlobals::Game::turnOnSound)
		{
			if (this->currentWin == 3)
				this->soundLose->stop();
			else
				this->soundWin->stop();
		}
		if (GameStateGame::showRetryDialog("Play New Game???", 25, 6))
		{
			this->load();
		}
	}
	if (this->game->willDraw())
	{
		this->vecScore.push_back(std::make_pair(this->score1, this->score2));
		this->vecScore.push_back(std::make_pair(this->score1, this->score2));
		this->game->updateScore(this->score1, this->score2);
		this->game->draw();
		if (this->isAi) LoadGame::playedGameCamp++; else LoadGame::playedGameMul++;
		this->countGame++;
		this->vecBoard.push_back(this->game->getLastBoard());
		if (EngineGlobals::Game::turnOnSound)
			this->soundDraw->play();
		Input::update(3500);
		if (EngineGlobals::Game::turnOnSound)
			this->soundDraw->stop();
		if (GameStateGame::showRetryDialog("Play New Game???", 25, 6))
		{
			this->load();
		}
	}
	if (this->game->willQuit()) this->willQuit = true;

}
void GameStateGame::draw()
{
	if (! this->willQuit)
		this->game->draw();
}
void GameStateGame::showDialog(std::string message, int width, int height)
{
	int x, y;
	getmaxyx(stdscr, y, x);
	int posX = x / 2 - width / 2;
	int posY = y / 2 - height / 2 - 2;

	Window dialog(posX, posY, width, height);
	dialog.borders(Window::BORDER_REGULAR);
	refresh();

	dialog.print(message, 4, 1, Colors::pair("white", "default", true));
	dialog.print("Press Any Key To Play", 2, 3, Colors::pair("cyan", "default"));
	dialog.print("Press  <ESC>  To Quit", 2, 4, Colors::pair("blue", "default"));
	dialog.refresh();
	refresh();

	if (EngineGlobals::Game::turnOnSound)
		this->sound->play();

	Input::update(-1);
	dialog.clear();
	if (EngineGlobals::Game::turnOnSound)
		this->sound->stop();
	if (Input::isPressed(27)) this->willQuit = true;
	else
	{
		this->isReady = true;
		this->game->isPlay = true;
	}
}

bool GameStateGame::showRetryDialog(std::string message, int width, int height)
{
	int x, y;
	getmaxyx(stdscr, y, x);
	int posX = x / 2 - width / 2;
	int posY = y / 2 - height / 2 - 2;

	Window dialog(posX, posY, width, height);
	dialog.borders(Window::BORDER_REGULAR);
	refresh();

	dialog.print(message, 4, 1, Colors::pair("white", "default", true));
	dialog.print("Press Any Key To Play", 2, 3, Colors::pair("cyan", "default"));
	dialog.print("Press  <ESC>  To Quit", 2, 4, Colors::pair("blue", "default"));
	dialog.refresh();
	refresh();
	if (EngineGlobals::Game::turnOnSound)
		this->sound->play();
	Input::update(-1);
	if (EngineGlobals::Game::turnOnSound)
		this->sound->stop();
	dialog.clear();
	if (Input::isPressed(27)) {
		this->willQuit = true;
		return false;
	}
	else
	{
		this->isReady = true;
		this->game->isPlay = true;
		return true;
	}
}
void GameStateGame::saveHistory()
{
	std::string tempFileName ="";
	std::vector<std::string> games = LoadStat::listGames();
	int siz = games.size() + 1;
	if (siz < 9)
	{
		this->filename = this->filename + "0" + (char)(siz + '0');
	}
	else
	{
		this->filename = this->filename + (char)(siz / 10 + '0') + (char)(siz % 10 + '0');
	}
	LoadStat::saveStat(this->filename, this->namePlayer1, this->namePlayer2, this->isAi, this->game->getSize(), EngineGlobals::Game::rule, this->score1, this->score2, this->countGame, this->vecScore, this->vecBoard);
}
