#include <Display/Layouts/LayoutMainMenu.hpp>
#include <Display/Colors.hpp>
#include <EngineGlobals.hpp>
#include <Helpers/Utils.hpp>
#include <GameStateMainMenu.hpp>
#include <Display/AnimationOX.hpp>


#include <iostream>

LayoutMainMenu::LayoutMainMenu(int width, int height):
	main(NULL),
	logo(NULL),
	menu(NULL),
	boardMenu(NULL),
	loadMenu(NULL),
	loadHelpWin(NULL),
	animationwin(NULL),
	animation(NULL)
{
	this->windowsInit(width, height);
}

LayoutMainMenu::~LayoutMainMenu() {
	this->windowsExit();
}

void LayoutMainMenu::windowsInit(int width, int height) {
	//  Layout chính
	clear();
	int current_height, current_width;
	getmaxyx(stdscr, current_height, current_width);


	int posX = 0;
	int posY = 0;

	posX = current_width/2 - width/2 - 10;
	posY = current_height/2 - height/2;

	this->main = new Window(posX, posY, width, height);
	this->main->borders(Window::BORDER_REGULAR);
	this->main->refresh();

	// menu chính
	this->menu = new Window(posX + width + 1, posY, 15, 9);
	this->menu->borders(Window::BORDER_FANCY);
	this->menu->setTitle("Main Menu");
	this->menu->refresh();

	this->loadHelpWin = new Window(posX + width + 1, posY + 15, 24, 5);

	posX = posX + width/2 - 10;
	posY = posY + height/2 - 3;
	this->boardMenu = new Window(posX, posY, 23, 7);
	this->boardMenu->setTitle("Choose Board Size");
	this->boardMenu->borders(Window::BORDER_FANCY);


	this->loadMenu = new Window(posX - 4, posY, 30, 13);
	this->loadMenu->setTitle("Choose Game");
	this->loadMenu->borders(Window::BORDER_FANCY);

	this->logo = new Window(this->main,
	                        20, 0,
	                        60, 7);
	this->logo->borders(Window::BORDER_NONE);



	// ANIMATION
	this->animationwin = new Window(this->main,
	                                0,
	                                this->logo->getH(),
	                                this->main->getW() - 2,
	                                this->main->getH() - this->logo->getH() - 1);

	this->animationwin->borders(Window::BORDER_NONE);

	this->animation = new AnimationOX(this->animationwin);

	this->animation->load();
}

void LayoutMainMenu::windowsExit() {
	SAFE_DELETE(this->menu);
	SAFE_DELETE(this->logo);
	SAFE_DELETE(this->animationwin);
	SAFE_DELETE(this->animation);
	SAFE_DELETE(this->boardMenu);
	SAFE_DELETE(this->loadMenu);
	SAFE_DELETE(this->loadHelpWin);
}

void LayoutMainMenu::draw(Menu* menu, int isSubMenu) {
	this->animation->update();

	this->main->clear();

	this->animation->draw();

	this->logo->clear();
	this->logo->print(Utils::String::split(" GGGGG     OOOOO    MM     MM    OOOOO    K      K   U     U\n"
	                                       "G     G   O     O   M M   M M   O     O   K    K     U     U\n"
	                                       "G         O     O   M  M M  M   O     O   K  K       U     U\n"
	                                       "G   GGG   O     O   M   M   M   O     O   KK         U     U\n"
	                                       "G     G   O     O   M       M   O     O   K  K       U     U\n"
	                                       " GGGGG     OOOOO    M       M    OOOOO    K    K      UUUUU ", '\n'),
	                  0,
	                  0,
	                  Colors::pair("cyan", "default", true));

	this->logo->refresh();

	// Yay!
	if (isSubMenu == 1)
	{
		this->boardMenu->clear();
		menu->draw(this->boardMenu);
		this->boardMenu->refresh();
	}
	else if (isSubMenu == 2)
	{
		this->loadHelpWin->setTitle("Help");
		this->loadHelpWin->borders(Window::BORDER_FANCY);

		this->loadMenu->clear();
		this->loadHelpWin->clear();

		menu->draw(this->loadMenu);
		this->loadHelpWin->print("Load game", 2, 2, Colors::pair("cyan", "default", true));
		this->loadHelpWin->print("Enter", 16, 2);
		this->loadHelpWin->print("Delete game", 2, 3, Colors::pair("cyan", "default", true));
		this->loadHelpWin->print("Delete", 16, 3);

		this->loadMenu->refresh();
		this->loadHelpWin->refresh();
	}
	else
	{
		this->loadHelpWin->setTitle("");
		this->loadHelpWin->borders(Window::BORDER_NONE);
		this->loadHelpWin->clear();
		this->loadHelpWin->refresh();

		this->menu->clear();

		menu->draw(this->menu);

		this->menu->refresh();

		this->main->refresh();
	}
	// NCURSES NEEDS THIS
	refresh();
}
