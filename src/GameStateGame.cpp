#include <GameStateGame.hpp>
#include <StateManager.hpp>
#include <Helpers/Utils.hpp>
#include <Input.hpp>
#include <Display/Window.hpp>
#include <StateManager.hpp>
#include <GameStateMainMenu.hpp>
#include <LoadGame.hpp>

GameStateGame::GameStateGame():
	game(NULL),
	willQuit(false),
	isReady(false)
{
	LoadGame::load(EngineGlobals::Game::currentGame);
	this->score1 = LoadGame::loadScore(1);
	this->score2 = LoadGame::loadScore(2);
}
GameStateGame::~GameStateGame()
{ }
void GameStateGame::load()
{
		this->game = new Game();
		if (!this->isReady && EngineGlobals::Game::currentGame != "")
			this->game->start(this->isReady, this->score1, this->score2, 1);
		else
			this->game->start(this->isReady, this->score1, this->score2, 0);
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
	if (!this->isReady)
	{
		this->game->draw();
		GameStateGame::showDialog("Are You Ready???", 25, 6);
	}
	if (this->game->willOver())
	{
		if (this->game->checkPlayerWin() == 1)
		{
			this->score1++;
		}
		else
		{
			this->score2++;
		}
		this->game->updateScore(this->score1, this->score2);
		this->game->draw();
		Input::update(4000);
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
	Input::update(-1);
	dialog.clear();
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
	Input::update(-1);
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
