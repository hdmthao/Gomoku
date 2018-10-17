#include <States/GameStateMainMenu.hpp>
#include <Input.hpp>
#include <EngineGlobals.hpp>

#include <StateManager.hpp>
#include <States/GameStateGame.hpp>

enum Label_Id {
	// Main Menu
	PVP=1337,
	PVC,
	LEVELS,
	LOAD,
	SETTINGS,
	CONTROL,
	STATISTICS,
	ABOUT,
	QUIT_GAME,

	// Level select Submenu
	RANDOM,

	// GUI Submenu
	SHOW_BORDERS,
	FANCY_BORDERS,
	OUTER_BORDER,
	USE_COLORS,
	CENTER_HORIZONTAL,
	CENTER_VERTICAL,

	// Controls Submenu
	CONTROLS_KEY_LEFT,
	CONTROLS_KEY_RIGHT,
	CONTROLS_KEY_UP,
	CONTROLS_KEY_DOWN,
	CONTROLS_KEY_PAUSE,
	CONTROLS_KEY_HELP,
	CONTROLS_KEY_QUIT,
	CONTROLS_DEFAULT
};

GameStateMainMenu::GameStateMainMenu():
	layout(NULL),
	menu(NULL),
	about(NULL)
{ }

void GameStateMainMenu::load() {
	this->layout = new LayoutMainMenu(100, 30);

	createMainMenu();

	this->about = new WindowAbout(100, 30);
}

void GameStateMainMenu::unload() {
	SAFE_DELETE(this->layout);
	SAFE_DELETE(this->menu);
}

void GameStateMainMenu::update() {

		this->menu->handleInput();

		if (this->menu->willQuit()) {
			switch(this->menu->currentID()) {
			case PVP:
				StateManager::change(new GameStateGame());
				break;
			case ABOUT:
				this->about->run();
				break;
			case QUIT_GAME:
				StateManager::quit();
				break;
			}
			this->menu->reset();
		}
}

void GameStateMainMenu::draw() {
		this->layout->draw(this->menu);
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
	item = new MenuItem("Quit", QUIT_GAME);
	menu->add(item);
}
