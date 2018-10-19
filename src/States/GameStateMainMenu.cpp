#include <States/GameStateMainMenu.hpp>
#include <Input.hpp>
#include <EngineGlobals.hpp>

#include <StateManager.hpp>
#include <States/GameStateGame.hpp>

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
	about(NULL),
	isActivatedPVP(false)
{ }

void GameStateMainMenu::load() {
	this->layout = new LayoutMainMenu(100, 30);

	createMainMenu();
	createBoardMenu();

	this->isActivatedPVP = false;
	this->about = new WindowAbout(100, 30);
}

void GameStateMainMenu::unload() {
	SAFE_DELETE(this->layout);
	SAFE_DELETE(this->menu);
	SAFE_DELETE(this->boardMenu);
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
	else
	{
		this->menu->handleInput();
		if (this->menu->willQuit())
		{
			switch(this->menu->currentID())
			{
				case PVP:
					this->isActivatedPVP = true;
					// StateManager::change(new GameStateGame());
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
		this->layout->draw(this->boardMenu, 0);
	}
	else
	{
		this->layout->draw(this->menu, 1);
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
