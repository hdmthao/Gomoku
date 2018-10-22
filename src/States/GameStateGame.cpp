#include <States/GameStateGame.hpp>
#include <StateManager.hpp>
#include <Helpers/Utils.hpp>
#include <Input.hpp>
#include <Display/Window.hpp>
#include <StateManager.hpp>
#include <States/GameStateMainMenu.hpp>

GameStateGame::GameStateGame():
	game(NULL),
	willQuit(false),
	isReady(false)
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
	if (!this->isReady)
	{
		this->game->draw();
		GameStateGame::showDialog("Are You Ready???", 25, 6);
	}
	if (this->game->willOver())
	{
		this->game->draw();
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
	if (Input::isPressed(27)) this->willQuit = true; else this->isReady = true;
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
		return true;
	}
}
