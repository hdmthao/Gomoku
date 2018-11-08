#include <GameStateMainMenu.hpp>
#include <Input.hpp>
#include <EngineGlobals.hpp>
#include <LoadGame.hpp>
#include <StateManager.hpp>
#include <GameStateGame.hpp>
#include <GameStateShow.hpp>
#include <iostream>

enum Label_Id {
	// Main Menu
	PVP=1337, PVC, LEVELS, LOAD, SETTINGS, CONTROL, STATISTICS, ABOUT, QUIT,

	//Setting Menu
	SIZE, SOUND, ICON,

	// Size Board Menu
	RETURN, TICTACTOE, SMALL, NORMAL, BIG, BIGEST,

	// Icon Menu
	CLASSIC, MIND, TIME, SOUL, POWER, REALITY, SPACE, MAKE,

	//Marvel Menu
	IRON, SPIDER, THANOS, CAPTAIN, HULK, PANTHER, THOR, DEADPOOL,

	XERATH, ELISE, YASUO, PANTHEON, RENEKTON, ANNIE, ORNN, IRELIA
};

GameStateMainMenu::GameStateMainMenu():
	layout(NULL),
	menu(NULL),
	boardMenu(NULL),
	iconMenu(NULL),
	marvelMenu(NULL),
	mobaMenu(NULL),
	loadMenu(NULL),
	settingMenu(NULL),
	about(NULL),
	statistic(NULL),
	music(NULL)
{ }

void GameStateMainMenu::load() {
	this->layout = new LayoutMainMenu(100, 30);

	createMainMenu();
	createBoardMenu();
	createLoadMenu();
	createMarvelMenu();
	createMobaMenu();
	createSettingMenu();
	createIconMenu();

	this->isActivatedPVP = false;
	this->isActivatedLOAD = false;
	this->isActivatedName1 = false;
	this->isActivatedName2 = false;
	this->isActivatedSetting = false;
	this->isActivatedSize = false;
	this->isActivatedIcon = false;
	this->XIcon = 88;
	this->OIcon = 79;

	this->about = new WindowAbout(100, 30);
	this->statistic = new WindowStatistic(100, 30);

	this->music = new sf::Music();

	this->music->openFromFile("/home/himt/cs/cs161/projects/Gomoku/src/Sound/MainMenu.wav");
	this->music->setLoop(true);
	if (EngineGlobals::Game::turnOnSound)
		this->music->play();

}

void GameStateMainMenu::unload() {
	SAFE_DELETE(this->layout);
	SAFE_DELETE(this->menu);
	SAFE_DELETE(this->boardMenu);
	SAFE_DELETE(this->iconMenu);
	SAFE_DELETE(this->loadMenu);
	SAFE_DELETE(this->marvelMenu);
	SAFE_DELETE(this->mobaMenu);
	SAFE_DELETE(this->settingMenu);

	this->music->stop();
	SAFE_DELETE(this->music);
}

void GameStateMainMenu::update()
{
	if (this->isActivatedName1)
	{
		this->marvelMenu->handleInput();
		if (this->marvelMenu->willQuit())
		{
			switch(this->marvelMenu->currentID())
			{
				case RETURN:
					this->isActivatedName1 = false;
					break;
				default:
					this->isActivatedName1 = false;
					this->isActivatedName2 = true;
					EngineGlobals::Game::setNamePlayer(this->marvelMenu->currentLabel(), 1);
					break;
			}
		}
		this->marvelMenu->reset();
	}
	else
	if (this->isActivatedName2)
	{
		this->mobaMenu->handleInput();
		if (this->mobaMenu->willQuit())
		{
			switch(this->mobaMenu->currentID())
			{
				case RETURN:
					this->isActivatedName2 = false;
					this->isActivatedName1 = true;
					break;
				default:
					this->isActivatedName2 = false;
					EngineGlobals::Game::setNamePlayer(this->mobaMenu->currentLabel(), 0);
					StateManager::change(new GameStateGame(false));
					break;
			}
		}
		this->mobaMenu->reset();
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
					StateManager::change(new GameStateGame(false));
					break;
			}
		}
		else if (this->loadMenu->willDelete())
		{
			LoadGame::removeLoadGame(this->loadMenu->currentLabel());
			createLoadMenu();
		}
		this->loadMenu->reset();
	}
	else
	if (this->isActivatedSetting)
	{
		this->settingMenu->handleInput();
		if (this->settingMenu->willQuit())
		{
			switch(this->settingMenu->currentID())
			{
				case RETURN:
					this->isActivatedSetting = false;
					break;
				case SIZE:
					this->isActivatedSetting = false;
					this->isActivatedSize = true;
					break;
				case SOUND:
					EngineGlobals::Game::setSound();
					if (EngineGlobals::Game::turnOnSound)
						this->music->play();
					else this->music->stop();
					createSettingMenu();
					break;
				case ICON:
					this->isActivatedSetting = false;
					this->isActivatedIcon = true;
					break;
				default:
					break;
			}
		}
		this->settingMenu->reset();
	}
	else
	if (this->isActivatedSize)
	{
		this->boardMenu->handleInput();
		if (this->boardMenu->willQuit())
		{
			switch(this->boardMenu->currentID())
			{
				case SMALL:
					EngineGlobals::Board::setGameStyle(EngineGlobals::Board::Style::SMALL);
					this->isActivatedSize = false;
					this->isActivatedSetting = true;
					break;
				case NORMAL:
					EngineGlobals::Board::setGameStyle(EngineGlobals::Board::Style::NORMAL);
					this->isActivatedSize = false;
					this->isActivatedSetting = true;
					break;
				case BIG:
					EngineGlobals::Board::setGameStyle(EngineGlobals::Board::Style::BIG);
					this->isActivatedSize = false;
					this->isActivatedSetting = true;
					break;
				case BIGEST:
					EngineGlobals::Board::setGameStyle(EngineGlobals::Board::Style::BIG);
					this->isActivatedSize = false;
					this->isActivatedSetting = true;
					break;
				default:
					break;
			}
		}
		this->boardMenu->reset();
	}
	else
	if (this->isActivatedIcon)
	{
		this->iconMenu->handleInput();
		if (this->iconMenu->willQuit())
		{
			int cur = 1;
			char c1 = '_';
			char c2 = '_';
			switch(this->iconMenu->currentID())
			{
				case CLASSIC:
					EngineGlobals::Board::setXIcon(88);
					EngineGlobals::Board::setOIcon(79);
					this->isActivatedIcon = false;
					this->isActivatedSetting = true;
					break;
				case MIND:
					EngineGlobals::Board::setXIcon(4194400);
					EngineGlobals::Board::setOIcon(4194427);
					this->isActivatedIcon = false;
					this->isActivatedSetting = true;
					break;
				case POWER:
					EngineGlobals::Board::setXIcon(4194409);
					EngineGlobals::Board::setOIcon(4194429);
					this->isActivatedIcon = false;
					this->isActivatedSetting = true;
					break;
				case SPACE:
					EngineGlobals::Board::setXIcon(4194407);
					EngineGlobals::Board::setOIcon(64);
					this->isActivatedIcon = false;
					this->isActivatedSetting = true;
					break;
				case REALITY:
					EngineGlobals::Board::setXIcon(4194349);
					EngineGlobals::Board::setOIcon(191);
					this->isActivatedIcon = false;
					this->isActivatedSetting = true;
					break;
				case TIME:
					EngineGlobals::Board::setXIcon(35);
					EngineGlobals::Board::setOIcon(42);
					this->isActivatedIcon = false;
					this->isActivatedSetting = true;
					break;
				case SOUL:
					EngineGlobals::Board::setXIcon(61);
					EngineGlobals::Board::setOIcon(36);
					this->isActivatedIcon = false;
					this->isActivatedSetting = true;
					break;
				case MAKE:
					while (1)
					{
						this->layout->draw(this->iconMenu, 6, cur, c1, c2);
						Input::update(-1);
						if (Input::isPressed('\n')) break;
						if (cur == 2 && Input::isPressed(KEY_LEFT))
						{
							c1 = '_';
							cur = 1;
							continue;
						}
						if (cur == 1)
						{
							c1 = Input::getIcon();
							if (c1 == ' ') {
								c1 = '_';
								cur = 1;
							} else
							cur = 2;
						} else
						if (cur == 2)
						{
							c2 = Input::getIcon();
							if (c2 == ' ')
							{
								c2 = '_';
								cur = 2;
							} else continue;
						}
					}
					if (c1 != '_' && c2 != '_')
					{
						this->XIcon = (int)c1;
						this->OIcon = (int)c2;
						EngineGlobals::Board::setXIcon(this->XIcon);
						EngineGlobals::Board::setOIcon(this->OIcon);
						this->isActivatedIcon = false;
						this->isActivatedSetting = true;
						break;
					} else break;
				default:
					break;
			}
		}
		this->iconMenu->reset();
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
					this->isActivatedName1 = true;
					break;
				case LOAD:
					this->isActivatedLOAD = true;
					break;
				case SETTINGS:
					this->isActivatedSetting = true;
					break;
				case STATISTICS:
					this->statistic->load();
					this->statistic->run();
					if (this->statistic->getGameShow() != "") StateManager::change(new GameStateShow(this->statistic->getGameShow()));
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
	if (this->isActivatedName1)
	{
		this->layout->draw(this->marvelMenu, 3);
	}
	else if (this->isActivatedName2)
	{
		this->layout->draw(this->mobaMenu, 4);
	}
	else if (this->isActivatedLOAD)
	{
		this->layout->draw(this->loadMenu, 2);
	}
	else if (this->isActivatedSetting)
	{
		this->layout->draw(this->settingMenu, 0);
	}
	else if (this->isActivatedSize)
	{
		this->layout->draw(this->boardMenu, 1);
	}
	else if (this->isActivatedIcon)
	{
		this->layout->draw(this->iconMenu, 5);
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
void GameStateMainMenu::createMarvelMenu()
{
	SAFE_DELETE(this->marvelMenu);

	this->marvelMenu = new Menu(1, 1, this->layout->nameMenu->getW() - 2, this->layout->nameMenu->getH() - 2);

	MenuItem* item;

	item = new MenuItem("Iron Man", IRON);
	marvelMenu->add(item);

	item = new MenuItem("Spider Man", SPIDER);
	marvelMenu->add(item);

	item = new MenuItem("Thanos", THANOS);
	marvelMenu->add(item);

	item = new MenuItem("Captain America", CAPTAIN);
	marvelMenu->add(item);

	item = new MenuItem("Hulk", HULK);
	marvelMenu->add(item);

	item = new MenuItem("Black Panther", PANTHER);
	marvelMenu->add(item);

	item = new MenuItem("Thor", THOR);
	marvelMenu->add(item);

	item = new MenuItem("Deadpool", DEADPOOL);
	marvelMenu->add(item);

	marvelMenu->addBlank();
	item = new MenuItem("Back", RETURN);
	marvelMenu->add(item);

}
void GameStateMainMenu::createMobaMenu()
{
	SAFE_DELETE(this->mobaMenu);

	this->mobaMenu = new Menu(1, 1, this->layout->nameMenu->getW() - 2, this->layout->nameMenu->getH() - 2);

	MenuItem* item;

	item = new MenuItem("Xerath", XERATH);
	mobaMenu->add(item);

	item = new MenuItem("Elise", ELISE);
	mobaMenu->add(item);

	item = new MenuItem("Yasuo", YASUO);
	mobaMenu->add(item);

	item = new MenuItem("Pantheon", PANTHEON);
	mobaMenu->add(item);

	item = new MenuItem("Renekton", RENEKTON);
	mobaMenu->add(item);

	item = new MenuItem("Annie", ANNIE);
	mobaMenu->add(item);

	item = new MenuItem("Ornn", ORNN);
	mobaMenu->add(item);

	item = new MenuItem("Irelia", IRELIA);
	mobaMenu->add(item);

	mobaMenu->addBlank();
	item = new MenuItem("Back", RETURN);
	mobaMenu->add(item);

}

void GameStateMainMenu::createBoardMenu()
{
	SAFE_DELETE(this->boardMenu);

	this->boardMenu = new Menu(1, 1, this->layout->boardMenu->getW() - 2, this->layout->boardMenu->getH() - 2);

	MenuItem* item;

	item = new MenuItem("Small     (9x9)", SMALL);
	boardMenu->add(item);

	item = new MenuItem("Normal    (13x13)", NORMAL);
	boardMenu->add(item);

	item = new MenuItem("Big       (19x19)", BIG);
	boardMenu->add(item);

	item = new MenuItem("Bigest    (25x25)", BIGEST);
	boardMenu->add(item);
}
void GameStateMainMenu::createLoadMenu()
{
	SAFE_DELETE(this->loadMenu);

	this->loadMenu = new Menu(1, 1, this->layout->loadMenu->getW() - 2, this->layout->loadMenu->getH() - 2);

	MenuItem* item;

	item = new MenuItem("Return Menu", RETURN);
	loadMenu->add(item);

	loadMenu->addBlank();

	std::vector<std::string> games = LoadGame::listGames();
	std::vector<std::string> infos = LoadGame::listInfos();


	for (unsigned int i = 0; i < games.size(); ++i) {
		for (int j = games[i].length(); j < 11; ++j) games[i] += " ";
		item = new MenuItem(games[i]+infos[i], i);
		loadMenu->add(item);
	}
}
void GameStateMainMenu::createSettingMenu()
{
	SAFE_DELETE(this->settingMenu);

	this->settingMenu = new Menu(1, 1, this->layout->menu->getW() - 2, this->layout->menu->getH() - 2);

	MenuItem* item;

	item = new MenuItem("Return", RETURN);
	settingMenu->add(item);

	settingMenu->addBlank();

	item = new MenuItem("Size Board", SIZE);
	settingMenu->add(item);

	if (EngineGlobals::Game::turnOnSound)
		item = new MenuItem("Sound OFF", SOUND);
	else
		item = new MenuItem("Sound ON", SOUND);
	settingMenu->add(item);

	item = new MenuItem("Icon", ICON);
	settingMenu->add(item);

}
void GameStateMainMenu::createIconMenu()
{
	SAFE_DELETE(this->iconMenu);

	this->iconMenu = new Menu(1, 1, this->layout->iconMenu->getW() - 2, this->layout->iconMenu->getH() - 2);

	MenuItem* item;

	item = new MenuItem("Classic Gem", CLASSIC);
	iconMenu->add(item);

	item = new MenuItem("Mind Gem", MIND);
	iconMenu->add(item);

	item = new MenuItem("Power Gem", POWER);
	iconMenu->add(item);

	item = new MenuItem("Space Gem", SPACE);
	iconMenu->add(item);

	item = new MenuItem("Time Gem", TIME);
	iconMenu->add(item);

	item = new MenuItem("Reality Gem", REALITY);
	iconMenu->add(item);

	item = new MenuItem("Soul Gem", SOUL);
	iconMenu->add(item);

	item = new MenuItem("Make A Gem", MAKE);
	iconMenu->add(item);
}
