#include <Display/Layouts/LayoutGame.hpp>
#include <EngineGlobals.hpp>
#include <Helpers/Utils.hpp>
#include <LoadGame.hpp>

LayoutGame::LayoutGame(Game* game, int width, int height):
	Layout(width, height),
	game(game),
	pause(NULL),
	help(NULL),
	infoGame(NULL),
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
	this->main->setTitle("GOMOKU");
	this->main->setTitle("Round " + toString(this->game->round), Window::TOP_RIGHT);
	if (this->game->isAi)
		this->main->setTitle("Campaign", Window::TOP_LEFT);
	else
		this->main->setTitle("Multiplayer", Window::TOP_LEFT);
	this->pause = new Window(this->main, this->main->getW() / 4, this->main->getH() / 2 - 3, this->main->getW() / 2, 7);
	this->pause->setTitle("Paused");

	this->help = new Window(130, 15, 24, 10);
	this->help->borders(Window::BORDER_FANCY);
	this->help->setTitle("Help");

	this->infoTop = new Window(130, 6, 24, 8);
	this->infoTop->borders(Window::BORDER_FANCY);
	this->infoTop->setTitle("");

	this->infoBot = new Window(130, 26, 24, 8);
	this->infoBot->borders(Window::BORDER_FANCY);
	this->infoBot->setTitle("");

	this->scoreBoardTop = new Window(this->infoTop, 10, 2, 11, 4);
	this->scoreBoardTop->borders(Window::BORDER_NONE);
	this->scoreBoardTop->setTitle("SCORE");

	this->scoreBoardBot = new Window(this->infoBot, 10, 2, 11, 4);
	this->scoreBoardBot->borders(Window::BORDER_NONE);
	this->scoreBoardBot->setTitle("SCORE");

	this->infoGame = new Window(5, 7, 37, 20);
	this->infoGame->borders(Window::BORDER_FANCY);
	this->infoGame->setTitle("Info Game");
}
void LayoutGame::windowsExit()
{
	SAFE_DELETE(this->infoTop);
	SAFE_DELETE(this->infoBot);
	SAFE_DELETE(this->scoreBoardTop);
	SAFE_DELETE(this->scoreBoardBot);
	SAFE_DELETE(this->pause);
	SAFE_DELETE(this->help);
	SAFE_DELETE(this->infoGame);

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
		this->help->print("Movement", 2, 3, Colors::pair("cyan", "default", true));
		this->help->print("AWSD", 14, 3);
		this->help->print("Undo", 2, 4, Colors::pair("cyan", "default", true));
		this->help->print("z", 17, 4);
		this->help->print("Resign \"GG\"", 2, 5, Colors::pair("cyan", "default", true));
		this->help->print("g", 17, 5);
		if (EngineGlobals::Game::turnOnSound)
			this->help->print("OFF Sound", 2, 6, Colors::pair("cyan", "default", true));
		else
			this->help->print("ON Sound", 2, 6, Colors::pair("cyan", "default", true));
		this->help->print("m", 17, 6);
		this->help->print("Pause", 2, 7, Colors::pair("cyan", "default", true));
		this->help->print("Esc", 17, 7);
		this->help->print("Quit", 2, 8, Colors::pair("cyan", "default", true));
		this->help->print("q", 17, 8);
		this->help->refresh();
	}
	this->game->board->draw(this->main, this->game->currentPlayer);

	this->main->refresh();

	string player1 = this->game->player1->getName();
	string player2 = this->game->player2->getName();
	this->infoTop->setTitle(player1);
	this->infoBot->setTitle(player2);

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
				this->infoTop->print(Utils::String::split("X   X\n"
														  "  X  \n"
														  "X   X\n", '\n'), 2, 2, true, Colors::pair("cyan", "default", true));
				this->infoBot->print(Utils::String::split(" o o \n"
														  "o   o\n"
														  " o o \n", '\n'), 2, 2, Colors::pair("black", "default", true));

				this->infoTop->print(player1 + " WIN^^", this->infoTop->getW() / 2 - (player1.size() + 6) / 2, 6, true, Colors::pair("magenta", "default", true));
				this->infoBot->print(player2 + " LOSE:\(", this->infoTop->getW() / 2 - (player2.size() + 7) / 2, 6, Colors::pair("black", "default"));

				if (EngineGlobals::Game::rule == 5)
				{
					this->infoTop->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
					this->infoBot->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
					this->drawCapture1(this->game->captured1);
					this->drawCapture2(this->game->captured2);
				}

				if (EngineGlobals::Game::AI != 0)
				{
					this->infoTop->print("Rating", 12, 4, Colors::pair("yellow", "default", true));
					this->drawRating(LoadGame::rating, true);
				}
				LayoutGame::drawNumberTop(this->game->player1->getScore(), true);
				LayoutGame::drawNumberBot(this->game->player2->getScore());

			}
			else
			{
				this->infoTop->print(Utils::String::split("X   X\n"
													  	  "  X  \n"
													  	  "X   X\n", '\n'), 2, 2, Colors::pair("black", "default", true));
				this->infoBot->print(Utils::String::split(" o o \n"
												  		  "o   o\n"
												  		  " o o \n", '\n'), 2, 2, true, Colors::pair("cyan", "default", true));
				this->infoTop->print(player1 + " LOSE:\(", this->infoTop->getW() / 2 - (player1.size() + 7) / 2, 6, Colors::pair("black", "default"));
				this->infoBot->print(player2 + " WIN^^", this->infoTop->getW() / 2 - (player2.size() + 7) / 2, 6, true, Colors::pair("magenta", "default", true));
				if (EngineGlobals::Game::rule == 5)
				{
					this->infoTop->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
					this->infoBot->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
					this->drawCapture1(this->game->captured1);
					this->drawCapture2(this->game->captured2);
				}
				if (EngineGlobals::Game::AI != 0)
				{
					this->infoTop->print("Rating", 12, 4, Colors::pair("yellow", "default", true));
					this->drawRating(LoadGame::rating);
				}
				LayoutGame::drawNumberTop(this->game->player1->getScore());
				LayoutGame::drawNumberBot(this->game->player2->getScore(), true);

			}
		}
		else if (this->game->willDraw())
		{
			this->infoTop->print(Utils::String::split("X   X\n"
													  "  X  \n"
													  "X   X\n", '\n'), 2, 2, Colors::pair("black", "default", true));
			this->infoBot->print(Utils::String::split(" o o \n"
													  "o   o\n"
													  " o o \n", '\n'), 2, 2, Colors::pair("cyan", "default", true));
			if (EngineGlobals::Game::rule == 5)
			{
				this->infoTop->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
				this->infoBot->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
				this->drawCapture1(this->game->captured1);
				this->drawCapture2(this->game->captured2);
			}

			if (EngineGlobals::Game::AI != 0)
			{
				this->infoTop->print("Rating", 12, 4, Colors::pair("yellow", "default", true));
				this->drawRating(LoadGame::rating);
			}
			this->infoTop->print("!!! D R A W !!!", this->infoTop->getW() / 2 - 6, 6, Colors::pair("magenta", "default", true));
			this->infoBot->print("!!! D R A W !!!", this->infoTop->getW() / 2 - 7, 6, Colors::pair("magenta", "default", true));
		}
		else
		{
			LayoutGame::drawNumberTop(this->game->player1->getScore());
			LayoutGame::drawNumberBot(this->game->player2->getScore());

			if (this->game->currentPlayer == Board::PLAYER_1)
			{
				this->infoTop->print(Utils::String::split("X   X\n"
													  	  "  X  \n"
													  	  "X   X\n", '\n'), 2, 2, Colors::pair("cyan", "default", true));
				this->infoBot->print(Utils::String::split(" o o \n"
														  "o   o\n"
														  " o o \n", '\n'), 2, 2, Colors::pair("black", "default", true));

				this->infoTop->print(player1 + "'s TURN", this->infoTop->getW() / 2 - (player1.size() + 7) / 2, 6, Colors::pair("white", "default", true));

				if (EngineGlobals::Game::rule == 5)
				{
					this->infoTop->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
					this->infoBot->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
					this->drawCapture1(this->game->captured1);
					this->drawCapture2(this->game->captured2);
				}
				if (EngineGlobals::Game::AI != 0)
				{
					this->infoTop->print("Rating", 12, 4, Colors::pair("yellow", "default", true));
					this->drawRating(LoadGame::rating);
				}
			}
			else
			{
				this->infoTop->print(Utils::String::split("X   X\n"
													  	  "  X  \n"
													  	  "X   X\n", '\n'), 2, 2, Colors::pair("black", "default", true));
				this->infoBot->print(Utils::String::split(" o o \n"
												  		  "o   o\n"
												  		  " o o \n", '\n'), 2, 2, Colors::pair("cyan", "default", true));

				this->infoBot->print(player2 + "'s TURN", this->infoBot->getW() / 2 - (player2.size() + 7) / 2, 6, Colors::pair("white", "default", true));
				if (EngineGlobals::Game::rule == 5)
				{
					this->infoTop->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
					this->infoBot->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
					this->drawCapture1(this->game->captured1);
					this->drawCapture2(this->game->captured2);
				}
				if (EngineGlobals::Game::AI != 0)
				{
					this->infoTop->print("Rating", 12, 4, Colors::pair("yellow", "default", true));
					this->drawRating(LoadGame::rating);
				}			}
		}
	}
	else
	{

		this->infoTop->clear();
		this->infoBot->clear();

		this->scoreBoardTop->clear();
		this->scoreBoardBot->clear();


		this->infoTop->print(Utils::String::split("X   X\n"
												  "  X  \n"
											  	  "X   X\n", '\n'), 2, 2, Colors::pair("black", "default", true));
		LayoutGame::drawNumberTop(this->game->player1->getScore());


		this->infoBot->print(Utils::String::split(" o o \n"
												  "o   o\n"
											  	  " o o \n", '\n'), 2, 2, Colors::pair("black", "default", true));
		LayoutGame::drawNumberBot(this->game->player2->getScore());

		if (EngineGlobals::Game::rule == 5)
		{
			this->infoTop->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
			this->infoBot->print("Captured", 12, 4, Colors::pair("yellow", "default", true));
			this->drawCapture1(this->game->captured1);
			this->drawCapture2(this->game->captured2);

		}

		if (EngineGlobals::Game::AI != 0)
		{
			this->infoTop->print("Rating", 12, 4, Colors::pair("yellow", "default", true));
			this->drawRating(LoadGame::rating);
		}

	}

	this->scoreBoardTop->refresh();
	this->scoreBoardBot->refresh();
	this->infoTop->refresh();
	this->infoBot->refresh();

	this->infoGame->clear();

	this->infoGame->print("Board Size", 2, 2, Colors::pair("cyan", "default", true));
	switch (EngineGlobals::Board::getSize()) {
		case 3:
			this->infoGame->print("3 x 3", 22, 2);
			break;
		case 9:
			this->infoGame->print("9 x 9", 22, 2);
			break;
		case 13:
			this->infoGame->print("13 x 13", 22, 2);
			break;
		case 19:
			this->infoGame->print("19 x 19", 22, 2);
			break;
		case 25:
			this->infoGame->print("25 x 25", 22, 2);
			break;
		default:
			this->infoGame->print("NULL", 22, 2);
			break;
	}

	this->infoGame->print(player1, 2, 4, Colors::pair("cyan", "default", true));
	this->infoGame->printChar(EngineGlobals::Board::XIcon, 25, 4, Colors::pair("yellow", "default", true));

	this->infoGame->print(player2, 2, 5, Colors::pair("cyan", "default", true));
	this->infoGame->printChar(EngineGlobals::Board::OIcon, 25, 5, Colors::pair("red", "default", true));

	this->infoGame->print("Game Rule", 2, 8, Colors::pair("cyan", "default", true));
	this->infoGame->print("Winning Score", 2, 9, Colors::pair("cyan", "default", true));
	this->infoGame->print("Description Rule", 2, 11, Colors::pair("cyan", "default", true));
	switch (EngineGlobals::Game::rule) {
		case 1:
			this->infoGame->print("Free-Style", 22, 8);
			this->infoGame->print("5 or More", 22, 9);
			this->infoGame->print(Utils::String::split("Requires a row of 5\n"
													   "or more stones for a win.\n", '\n'), 3, 12);
			break;
		case 2:
			this->infoGame->print("Caro", 22, 8);
			this->infoGame->print("5 or More", 22, 9);
			this->infoGame->print(Utils::String::split("Requires unbroken row of 5\n"
														"stones and this row must not\n"
														"be blocked at either end.\n", '\n'), 3, 12);
			break;
		case 3:
			this->infoGame->print("Standard", 22, 8);
			this->infoGame->print("5", 25, 9);
			this->infoGame->print(Utils::String::split("Requires a row of exactly 5\n"
													   "stones for a win (rows of six\n"
													   "or more, called overlines\n"
													   "do not count.", '\n'), 3, 12);
			break;
		case 4:
			this->infoGame->print("Tic-Tac-Toe", 22, 8);
			this->infoGame->print("3", 25, 9);
			this->infoGame->print(Utils::String::split("Requires a row of 3\n"
													   "stones for a win.\n", '\n'), 3, 12);
			break;
		case 5:
			this->infoGame->print("Pente", 22, 8);
			this->infoGame->print(Utils::String::split("5 or More\n"
													   "Or 5 Capture\n", '\n'), 22, 9);
			this->infoGame->print(Utils::String::split("Requires a row of 5 or more\n"
													   "stones or capture 10 enemy stones\n"
													   "You can capture 2 connected enemy\n"
													   "stones by flanking them with your\n"
													   "own stones.\n", '\n'), 2, 12);
			this->infoGame->print("More About Rule", 2, 17, Colors::pair("cyan", "default", true));
			this->infoGame->print("yourturnmyturn.com/rules/pente.php", 2, 18);
			break;
		case 6:
			this->infoGame->print("Connect6", 22, 8);
			this->infoGame->print("6 Or More", 22 , 9);
			this->infoGame->print(Utils::String::split("Requires a row of 6 or more stones\n"
																								 "The first player putting one stone\n"
																								 "on board. Subsequently, two player\n"
																								 "take turn, placing two stones on\n"
																								 "two different unoccupied spaces\n"
																								 "each turn.\n",
																							 		'\n'), 2, 12);
			break;
		case 7:
		case 8:
		default:
			this->infoGame->print("NULL", 22, 8);
			this->infoGame->print("NULL", 22, 9);
			this->infoGame->print("NULL", 3, 12);
	}
	this->infoGame->refresh();


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
void LayoutGame::drawCapture1(int number, bool isVip)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < number; ++i)
	{
		if (isVip)
		{
			this->infoTop->printChar(ACS_DIAMOND, 11 + x*2, 5 + y, true, Colors::pair("white", "default", true));
		}
		else
		{
			this->infoTop->printChar(ACS_DIAMOND, 11 + x*2, 5 + y, Colors::pair("white", "default", true));
		}
		x++;
		if (i == 4)
		{
			y++;
			x = 0;
			return;
		}
	}
}
void LayoutGame::drawCapture2(int number, bool isVip)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < number; ++i)
	{
		if (isVip)
		{
			this->infoBot->printChar(ACS_DIAMOND, 11 + x*2, 5 + y, true, Colors::pair("white", "default", true));
		}
		else
		{
			this->infoBot->printChar(ACS_DIAMOND, 11 + x*2, 5 + y, Colors::pair("white", "default", true));
		}
		x++;
		if (i == 4)
		{
			y++;
			x = 0;
			return;
		}
	}
}
std::string LayoutGame::toString(int num)
{
	if (num == 0) return "0";
	std::string tmp = "";
	while (num != 0)
	{
		tmp = (char)(num % 10 + '0') + tmp;
		num /= 10;
	}
	return tmp;
}
void LayoutGame::drawRating(int number, bool isVip)
{
	string s = "";
	while (number != 0)
	{
		s = (char)(number % 10 + '0') + s;
		number/=10;
	}
	if (isVip)
	{
		this->infoTop->print(s, 13, 5, true, Colors::pair("white", "default", true));
	}
	else
	{
		this->infoTop->print(s, 13, 5 , Colors::pair("white", "default", true));
	}
}
