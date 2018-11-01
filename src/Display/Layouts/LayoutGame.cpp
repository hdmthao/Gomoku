#include <Display/Layouts/LayoutGame.hpp>
#include <EngineGlobals.hpp>
#include <Helpers/Utils.hpp>

LayoutGame::LayoutGame(Game* game, int width, int height):
	Layout(width, height),
	game(game),
	pause(NULL),
	help(NULL),
	infoTop(NULL),
	infoBot(NULL),
	scoreBoardTop(NULL),
	scoreBoardBot(NULL)
{
	this->windowsInit();
}
LayoutGame::~LayoutGame()
{
	this->windowsExit();
}
void LayoutGame::windowsInit()
{
	Layout::windowsInit();
	this->main->setTitle("Gomoku - PvP Mode");


	this->pause = new Window(this->main, this->main->getW() / 4, this->main->getH() / 2 - 3, this->main->getW() / 2, 7);
	this->pause->setTitle("Paused");

	this->help = new Window(130, 15, 24, 10);
	this->help->borders(Window::BORDER_FANCY);
	this->help->setTitle("Help");

	this->infoTop = new Window(130, 6, 24, 8);
	this->infoTop->borders(Window::BORDER_FANCY);
	this->infoTop->setTitle("YASUO");

	this->infoBot = new Window(130, 26, 24, 8);
	this->infoBot->borders(Window::BORDER_FANCY);
	this->infoBot->setTitle("INVOKER");

	this->scoreBoardTop = new Window(this->infoTop, 10, 2, 11, 4);
	this->scoreBoardTop->borders(Window::BORDER_NONE);
	this->scoreBoardTop->setTitle("SCORE");

	this->scoreBoardBot = new Window(this->infoBot, 10, 2, 11, 4);
	this->scoreBoardBot->borders(Window::BORDER_NONE);
	this->scoreBoardBot->setTitle("SCORE");

}
void LayoutGame::windowsExit()
{
	SAFE_DELETE(this->infoTop);
	SAFE_DELETE(this->infoBot);
	SAFE_DELETE(this->scoreBoardTop);
	SAFE_DELETE(this->scoreBoardBot);
	SAFE_DELETE(this->pause);
	SAFE_DELETE(this->help);

	this->main->clear(); // clear() as in Window
	this->main->refresh(); // clear() as in Window

	Layout::windowsExit();
}
void LayoutGame::draw(Menu *menu, std::string filename, bool isDefault)
{
	if (! this->game)
		return;

	this->main->clear();
	this->help->clear();

	if (this->game->userAskedToSaveGame)
	{
		this->pause->setTitle("Save Game");
		this->pause->clear();
		this->pause->print("Name:", 4, 1, Colors::pair("black", "default", true));
		if (isDefault)
		{
			this->pause->print(filename, 9, 1, Colors::pair("black", "default", true));
			this->pause->print("Default name is \"GOMOKU_xx\"", 2, 3);
		}
		else
		{
			this->pause->print(filename, 9, 1, Colors::pair("cyan", "default", true));
		}
		this->pause->print("Must has at most 9 characters", 2, 4);
		this->pause->print("Allow alphabet character, number, \'_\'", 2, 5);
		this->pause->refresh();

		this->help->print("Save and quit", 2, 2, Colors::pair("cyan", "default", true));
		this->help->print("Enter", 16, 2);
		this->help->print("Back", 2, 3, Colors::pair("cyan", "default", true));
		this->help->print("Esc", 16, 3);
		this->help->refresh();
		refresh();
		return;
	}
	else if (this->game->isPause)
	{
		this->pause->clear();
		menu->draw(this->pause);
		this->pause->refresh();

		this->help->print("Choose option", 2, 2, Colors::pair("cyan", "default", true));
		this->help->print("Enter", 16, 2);
		this->help->print("Back", 2, 3, Colors::pair("cyan", "default", true));
		this->help->print("Esc", 16, 3);
		this->help->refresh();
		refresh();
		return;
	}
	else
	{
		this->help->print("Movement", 2, 2, Colors::pair("cyan", "default", true));
		this->help->print("Key-Arrow", 14, 2);
		this->help->print("Undo", 2, 3, Colors::pair("cyan", "default", true));
		this->help->print("z", 14, 3);
		this->help->print("Resign \"GG\"", 2, 4, Colors::pair("cyan", "default", true));
		this->help->print("g", 14, 4);
		this->help->print("Rule", 2, 5, Colors::pair("cyan", "default", true));
		this->help->print("r", 14, 5);
		this->help->print("Pause", 2, 6, Colors::pair("cyan", "default", true));
		this->help->print("Esc", 14, 6);
		this->help->print("Quit", 2, 7, Colors::pair("cyan", "default", true));
		this->help->print("q", 14, 7);
		this->help->refresh();
	}
	this->game->board->draw(this->main, this->game->currentPlayer);

	this->main->refresh();


	if (this->game->isPlaying())
	{

		if (this->game->currentPlayer == Board::PLAYER_1)
		{
			this->infoTop->borders(Window::BORDER_GAME);
			this->infoBot->borders(Window::BORDER_FANCY);
		}
		else
		{
			this->infoTop->borders(Window::BORDER_FANCY);
			this->infoBot->borders(Window::BORDER_GAME);
		}

		this->infoTop->clear();
		this->infoBot->clear();
		this->scoreBoardTop->clear();
		this->scoreBoardBot->clear();



		if (this->game->willOver())
		{
			if (this->game->currentPlayer == Board::PLAYER_1)
			{
				this->infoTop->print(Utils::String::split("#   #\n"
														  "  #  \n"
														  "#   #\n", '\n'), 2, 2, Colors::pair("cyan", "default", true));
				this->infoBot->print(Utils::String::split(" o o \n"
														  "o   o\n"
														  " o o \n", '\n'), 2, 2, Colors::pair("black", "default", true));

				this->infoTop->print("YASUO WIN^^", this->infoTop->getW() / 2 - 6, 6, true, Colors::pair("magenta", "default", true));
				this->infoBot->print("INVOKER LOSE:\(", this->infoTop->getW() / 2 - 7, 6, Colors::pair("black", "default"));

				LayoutGame::drawNumberTop(this->game->player1->getScore(), true);
				LayoutGame::drawNumberBot(this->game->player2->getScore());

			}
			else
			{
				this->infoTop->print(Utils::String::split("#   #\n"
													  	  "  #  \n"
													  	  "#   #\n", '\n'), 2, 2, Colors::pair("black", "default", true));
				this->infoBot->print(Utils::String::split(" o o \n"
												  		  "o   o\n"
												  		  " o o \n", '\n'), 2, 2, Colors::pair("cyan", "default", true));
				this->infoTop->print("YASUO LOSE:\(", this->infoTop->getW() / 2 - 6, 6, Colors::pair("black", "default"));
				this->infoBot->print("INVOKER WIN^^", this->infoTop->getW() / 2 - 7, 6, true, Colors::pair("magenta", "default", true));
				LayoutGame::drawNumberTop(this->game->player1->getScore());
				LayoutGame::drawNumberBot(this->game->player2->getScore(), true);

			}
		}
		else
		{
			LayoutGame::drawNumberTop(this->game->player1->getScore());
			LayoutGame::drawNumberBot(this->game->player2->getScore());

			if (this->game->currentPlayer == Board::PLAYER_1)
			{
				this->infoTop->print(Utils::String::split("#   #\n"
													  	  "  #  \n"
													  	  "#   #\n", '\n'), 2, 2, Colors::pair("cyan", "default", true));
				this->infoBot->print(Utils::String::split(" o o \n"
														  "o   o\n"
														  " o o \n", '\n'), 2, 2, Colors::pair("black", "default", true));

				this->infoTop->print("YASUO's TURN", this->infoTop->getW() / 2 - 6, 6, Colors::pair("white", "default", true));

			}
			else
			{
				this->infoTop->print(Utils::String::split("#   #\n"
													  	  "  #  \n"
													  	  "#   #\n", '\n'), 2, 2, Colors::pair("black", "default", true));
				this->infoBot->print(Utils::String::split(" o o \n"
												  		  "o   o\n"
												  		  " o o \n", '\n'), 2, 2, Colors::pair("cyan", "default", true));

				this->infoBot->print("INVOKER's TURN", this->infoBot->getW() / 2 - 7, 6, Colors::pair("white", "default", true));
			}
		}
	}
	else
	{

		this->infoTop->clear();
		this->infoBot->clear();

		this->scoreBoardTop->clear();
		this->scoreBoardBot->clear();


		this->infoTop->print(Utils::String::split("#   #\n"
												  "  #  \n"
											  	  "#   #\n", '\n'), 2, 2, Colors::pair("black", "default", true));
		LayoutGame::drawNumberTop(this->game->player1->getScore());


		this->infoBot->print(Utils::String::split(" o o \n"
												  "o   o\n"
											  	  " o o \n", '\n'), 2, 2, Colors::pair("black", "default", true));
		LayoutGame::drawNumberBot(this->game->player2->getScore());

	}

	this->scoreBoardTop->refresh();
	this->scoreBoardBot->refresh();
	this->infoTop->refresh();
	this->infoBot->refresh();
	refresh();
}
void LayoutGame::drawNumberTop(int number, bool isVip)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < number; ++i)
	{
		if (isVip)
		{
			this->scoreBoardTop->printChar(ACS_DIAMOND, 1 + x*2, 1 + y, true, Colors::pair("white", "default", true));
		}
		else
		{
			this->scoreBoardTop->printChar(ACS_DIAMOND, 1 + x*2, 1 + y, Colors::pair("white", "default", true));
		}
		x++;
		if (i == 4)
		{
			y++;
			x = 0;
		}
	}
}
void LayoutGame::drawNumberBot(int number, bool isVip)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < number; ++i)
	{
		if (isVip)
		{
			this->scoreBoardBot->printChar(ACS_DIAMOND, 1 + x*2, 1 + y, true, Colors::pair("white", "default", true));
		}
		else
		{
			this->scoreBoardBot->printChar(ACS_DIAMOND, 1 + x*2, 1 + y, Colors::pair("white", "default", true));
		}
		x++;
		if (i == 4)
		{
			y++;
			x = 0;
		}
	}
}
