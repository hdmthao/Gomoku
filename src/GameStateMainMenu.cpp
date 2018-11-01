#include <GameStateMainMenu.hpp>
#include <Input.hpp>
#include <EngineGlobals.hpp>
#include <LoadGame.hpp>
#include <StateManager.hpp>
#include <GameStateGame.hpp>
#include <iostream>

enum Label_Id {
	// Main Menu
	PVP=1337, PVC, LEVELS, LOAD, SETTINGS, CONTROL, STATISTICS, ABOUT, QUIT,

	// Size Board Menu
	RETURN, TICTACTOE, SMALL, NORMAL, BIG

};

GameStateMainMenu::GameStateMainMenu():
	layout(NULL),
	menu(NULL),
	boardMenu(NULL),
	loadMenu(NULL),
	about(NULL)
{ }

void GameStateMainMenu::load() {
	this->layout = new LayoutMainMenu(100, 30);

	createMainMenu();
	createBoardMenu();
	createLoadMenu();

	this->isActivatedPVP = false;
	this->isActivatedLOAD = false;
	this->about = new WindowAbout(100, 30);
}

void GameStateMainMenu::unload() {
	SAFE_DELETE(this->layout);
	SAFE_DELETE(this->menu);
	SAFE_DELETE(this->boardMenu);
	SAFE_DELETE(this->loadMenu);
}

void GameStateMainMenu::update()
{
	if (this->isActivatedPVP)
	{
		this->boardMenu->handleInput();
		if (this->boardMenu->willQuit())
		{
			switch(this->boardMenu->currentID())
			{
				case TICTACTOE:
					this->isActivatedPVP = false;
					EngineGlobals::Board::setGameStyle(EngineGlobals::Board::TICTACTOE);
					StateManager::change(new GameStateGame());
					break;
				case SMALL:
					this->isActivatedPVP = false;
					EngineGlobals::Board::setGameStyle(EngineGlobals::Board::SMALL);
					StateManager::change(new GameStateGame());
					break;
				case NORMAL:
					this->isActivatedPVP = false;
					EngineGlobals::Board::setGameStyle(EngineGlobals::Board::NORMAL);
					StateManager::change(new GameStateGame());
					break;
				case BIG:
					this->isActivatedPVP = false;
					EngineGlobals::Board::setGameStyle(EngineGlobals::Board::BIG);
					StateManager::change(new GameStateGame());
					break;
				case RETURN:
					this->isActivatedPVP = false;
					break;
			}
			this->boardMenu->reset();
		}
	}
	else if (this->isActivatedLOAD)
	{
		this->loadMenu->handleInput();
		if(this->loadMenu->willQuit())
		{
			switch(this->loadMenu->currentID())
			{
				case RETURN:
					this->isActivatedLOAD = false;
					break;
				default:
					EngineGlobals::Game::setLoadGame(this->loadMenu->currentLabel());
					StateManager::change(new GameStateGame());
					break;
			}
		}
		this->loadMenu->reset();
	}
	else
	{
		this->menu->handleInput();
		if (this->menu->willQuit())
		{
			switch(this->menu->currentID())
			{
				case PVP:
					EngineGlobals::Game::setLoadGame("");
					this->isActivatedPVP = true;
					break;
				case LOAD:
					this->isActivatedLOAD = true;
					break;
				case ABOUT:
					this->about->run();
					break;
				case QUIT:
					StateManager::quit();
					break;
			}

			this->menu->reset();
		}
	}
}

void GameStateMainMenu::draw() {
	if (this->isActivatedPVP)
	{
		this->layout->draw(this->boardMenu, 1);
	}
	else if (this->isActivatedLOAD)
	{
		this->layout->draw(this->loadMenu, 2);
	}
	else
	{
		this->layout->draw(this->menu, 0);
	}
}

void GameStateMainMenu::createMainMenu() {
	SAFE_DELETE(this->menu);

	// Khởi tạo menu chính

	this->menu = new Menu(1,
	                      1,
	                      this->layout->menu->getW() - 2,
	                      this->layout->menu->getH() - 2);

	MenuItem* item;

	// Chế độ PvP
	item = new MenuItem("PvP", PVP);
	menu->add(item);

	// Chế độ PvC
	item = new MenuItem("PvC", PVC);
	menu->add(item);

	// Tải game đã lưu
	item = new MenuItem("Load", LOAD);
	menu->add(item);

	// cài đặt game
	item = new MenuItem("Settings", SETTINGS);
	menu->add(item);

	// statistic
	item = new MenuItem("Statistics", STATISTICS);
	menu->add(item);

	// about us
	item = new MenuItem("About Us", ABOUT);
	menu->add(item);

	// Thoát
	item = new MenuItem("Quit", QUIT);
	menu->add(item);
}
void GameStateMainMenu::createBoardMenu()
{
	SAFE_DELETE(this->boardMenu);

	this->boardMenu = new Menu(1, 1, this->layout->boardMenu->getW() - 2, this->layout->boardMenu->getH() - 2);

	MenuItem* item;

	item = new MenuItem("Normal    (13x13)", NORMAL);
	boardMenu->add(item);

	item = new MenuItem("TicTacToe (3x3)", TICTACTOE);
	boardMenu->add(item);

	item = new MenuItem("Small     (9x9)", SMALL);
	boardMenu->add(item);

	item = new MenuItem("Big       (19x19)", BIG);
	boardMenu->add(item);
	item = new MenuItem("Return Menu", RETURN);
	boardMenu->add(item);
}
void GameStateMainMenu::createLoadMenu()
{
	SAFE_DELETE(this->loadMenu);

	this->loadMenu = new Menu(1, 1, this->layout->loadMenu->getW() - 2, this->layout->loadMenu->getH() - 2);

	MenuItem* item;

	std::vector<std::string> games = LoadGame::listGames();
	std::vector<std::string> infos = LoadGame::listInfos();

	for (unsigned int i = 0; i < games.size(); ++i) {
		for (int j = games[i].length(); j < 11; ++j) games[i] += " ";
		item = new MenuItem(games[i]+infos[i], i);
		loadMenu->add(item);
	}
	item = new MenuItem("Return Menu", RETURN);
	loadMenu->add(item);
}
