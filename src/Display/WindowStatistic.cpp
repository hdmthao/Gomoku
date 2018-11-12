#include <Display/WindowStatistic.hpp>
#include <Display/Colors.hpp>
#include <EngineGlobals.hpp>
#include <Input.hpp>
#include <Helpers/Utils.hpp>
#include <LoadGame.hpp>
#include <LoadStat.hpp>
#include <iostream>

WindowStatistic::WindowStatistic(int screenWidth, int screenHeight) {
	int width  = 60;
	int height = 18;

	int windowx = screenWidth/2 - 4;
	int windowy = screenHeight/2 - 1;

	this->show = "";
	this->main = new Window(windowx, windowy, width, height);

	this->stats = new Window(this->main, 0, 0, 0, 0);
	this->stats->borders(Window::BORDER_INFO);


	this->history = new Window(this->main, 0, 0, 0, 0);
	this->history->borders(Window::BORDER_INFO);

	this->helpWin = new Window(127, 20, 24, 5);

}
WindowStatistic::~WindowStatistic()
{
	SAFE_DELETE(this->main);
	SAFE_DELETE(this->stats);
	SAFE_DELETE(this->history);
	SAFE_DELETE(this->helpWin);
}
void WindowStatistic::load()
{
    LoadGame::loadStatictis();
    this->rating = LoadGame::loadRating();
    this->playedGameMul = LoadGame::loadPlayedMul();
    this->playedGameCamp = LoadGame::loadPlayedCamp();
    this->topCharacterMarvel = LoadGame::loadMarvel();
    this->topCharacterMoba = LoadGame::loadMoba();
    this->winGame = LoadGame::loadWin();
    this->winRate = LoadGame::loadWinRate();

	listInfos = LoadStat::listGames();
	createHistory();

}
void WindowStatistic::run()
{
	int activatedIndex = 0;

	while (true)
	{
		// Tải trang
		this->main->clear();
		if (activatedIndex == 0) this->stats->clear(); else this->history->clear();
		this->helpWin->setTitle("Help");
		this->helpWin->borders(Window::BORDER_FANCY);
		this->helpWin->clear();

		this->main->print(((activatedIndex == 0) ?
		                   "[Stats]" :
		                   " Stats "),
		                  21,
		                  0,
		                  ((activatedIndex == 0) ?
		                   Colors::pair("yellow", "default", true) :
		                   Colors::pair("red", "default", true)));

		this->main->print(((activatedIndex == 1) ?
		                   "[History]" :
		                   " History "),
		                  29,
		                  0,
		                  ((activatedIndex == 1) ?
						   Colors::pair("yellow", "default", true) :
		                   Colors::pair("red", "default", true)));

		if (activatedIndex == 0) {
			this->helpWin->print("History", 2, 2, Colors::pair("cyan", "default", true));
			this->helpWin->print("Key-Right", 14, 2);
			this->helpWin->print("Back", 2, 3, Colors::pair("cyan", "default", true));
			this->helpWin->print("Esc", 14, 3);
			if (this->rating >= 3000)
            {
                this->stats->print(" L", 16, 2, Colors::pair("white", "default"));
                this->stats->print("e", 18, 2, Colors::pair("black", "default", true));
                this->stats->print("g", 19, 2, Colors::pair("green", "default"));
                this->stats->print("e", 20, 2, Colors::pair("cyan", "default"));
                this->stats->print("n", 21, 2, Colors::pair("blue", "default"));
                this->stats->print("d", 22, 2, Colors::pair("magenta", "default"));
                this->stats->print("a", 23, 2, Colors::pair("yellow", "default"));
                this->stats->print("r", 24, 2, Colors::pair("red", "default"));
                this->stats->print("y ", 25, 2, Colors::pair("white", "default"));
                this->stats->print("Grandmaster ", 27, 2, Colors::pair("red", "default"));
                this->stats->printChar(ACS_DIAMOND, 19, 3, Colors::pair("yellow", "default", true));
                this->stats->print(" I", 20, 3, Colors::pair("black", "default"));
                this->stats->print("_Love_Taylor ", 22, 3, Colors::pair("red", "default", true));
                this->stats->printChar(ACS_DIAMOND, 35, 3, Colors::pair("yellow", "default", true));

            } else if (this->rating >= 2400)
            {
                this->stats->print(" Grandmaster ", 21, 2, Colors::pair("red", "default"));
                this->stats->printChar(ACS_DIAMOND, 19, 3, Colors::pair("yellow", "default", true));
                this->stats->print(" I_Love_Taylor ", 20, 3, Colors::pair("red", "default", true));
                this->stats->printChar(ACS_DIAMOND, 35, 3, Colors::pair("yellow", "default", true));

            } else if (this->rating >= 2100)
            {
                this->stats->print(" Master ", 24, 2, Colors::pair("yellow", "default"));
                this->stats->printChar(ACS_DIAMOND, 19, 3, Colors::pair("yellow", "default", true));
                this->stats->print(" I_Love_Taylor ", 20, 3, Colors::pair("yellow", "default", true));
                this->stats->printChar(ACS_DIAMOND, 35, 3, Colors::pair("yellow", "default", true));
            } else if (this->rating >= 1900)
            {
                this->stats->print(" Candidate Master ", 19, 2, Colors::pair("magenta", "default"));
                this->stats->printChar(ACS_DIAMOND, 19, 3, Colors::pair("yellow", "default", true));
                this->stats->print(" I_Love_Taylor ", 20, 3, Colors::pair("magenta", "default", true));
                this->stats->printChar(ACS_DIAMOND, 35, 3, Colors::pair("yellow", "default", true));
            } else if (this->rating >= 1600)
            {
                this->stats->print(" Expert ", 23, 2, Colors::pair("blue", "default"));
                this->stats->printChar(ACS_DIAMOND, 18, 3, Colors::pair("yellow", "default", true));
                this->stats->print(" I_Love_Taylor ", 19, 3, Colors::pair("blue", "default", true));
                this->stats->printChar(ACS_DIAMOND, 34, 3, Colors::pair("yellow", "default", true));
            } else if (this->rating >= 1400)
            {
                this->stats->print(" Specialist ", 22, 2, Colors::pair("cyan", "default"));
                this->stats->printChar(ACS_DIAMOND, 19, 3, Colors::pair("yellow", "default", true));
                this->stats->print(" I_Love_Taylor ", 20, 3, Colors::pair("cyan", "default", true));
                this->stats->printChar(ACS_DIAMOND, 35, 3, Colors::pair("yellow", "default", true));
            } else if (this->rating >= 1200)
            {
                this->stats->print(" Pupil ", 23, 2, Colors::pair("green", "default"));
                this->stats->printChar(ACS_DIAMOND, 18, 3, Colors::pair("yellow", "default", true));
                this->stats->print(" I_Love_Taylor ", 19, 3, Colors::pair("green", "default", true));
                this->stats->printChar(ACS_DIAMOND, 34, 3, Colors::pair("yellow", "default", true));
            } else
            {
                this->stats->print(" Newbie ", 23, 2, Colors::pair("black", "default", true));
                this->stats->printChar(ACS_DIAMOND, 18, 3, Colors::pair("yellow", "default", true));
                this->stats->print(" I_Love_Taylor ", 19, 3, Colors::pair("black", "default", true));
                this->stats->printChar(ACS_DIAMOND, 34, 3, Colors::pair("yellow", "default", true));
            }

            this->stats->print("Win Rating   ", 3, 5, Colors::pair("yellow", "default", true));
            this->stats->print(this->toString(this->rating), 18, 5, Colors::pair("white", "default", true));
            this->stats->print("MMR", 23, 5);

            this->stats->print("Multiplayer", 9, 8, Colors::pair("yellow", "default", true));

            this->stats->print("Play", 4, 10, Colors::pair("black", "default", true));
            this->stats->print(this->toString(this->playedGameMul), 14, 10, Colors::pair("white", "default", true));
            this->stats->print("rounds", 19, 10);

            this->stats->print("HotPlayer1st", 4, 11, Colors::pair("black", "default", true));
            this->stats->print(this->topCharacterMarvel, 19, 11, Colors::pair("white", "default", true));

            this->stats->print("HotPlayer2st", 4, 12, Colors::pair("black", "default", true));
            this->stats->print(this->topCharacterMoba, 19, 12, Colors::pair("white", "default", true));


            this->stats->print("Campaign", 40, 8, Colors::pair("yellow", "default", true));

            this->stats->print("Play", 35, 10, Colors::pair("black", "default", true));
            this->stats->print(this->toString(this->playedGameCamp), 45, 10);
            this->stats->print("rounds", 50, 10);

            this->stats->print("Wins", 35, 11, Colors::pair("black", "default", true));
            this->stats->print(this->toString(this->winGame), 45, 11);
            this->stats->print("rounds", 50, 11);

            this->stats->print("Win Rate", 35, 12, Colors::pair("black", "default", true));
            this->stats->print(this->winRate + " %", 45, 12);
		}
		else if (activatedIndex == 1)
		{
			this->helpWin->print("Statistic", 2, 2, Colors::pair("cyan", "default", true));
			this->helpWin->print("Key-Left", 14, 2);
			this->helpWin->print("Back", 2, 3, Colors::pair("cyan", "default", true));
			this->helpWin->print("Esc", 14, 3);

			this->historyMenu->draw(this->history);
		}

		if (activatedIndex == 0) this->stats->refresh(); else
		{
			this->history->refresh();
		}

		this->helpWin->refresh();
		this->main->refresh();
		refresh();

		if (activatedIndex != 0)
		{
			this->historyMenu->handleInput();
			if (this->historyMenu->willQuit())
			{
				this->show = getName(this->historyMenu->currentLabel());
				return;
			}
		}

		Input::update();

		if (Input::isPressed(KEY_LEFT))
		{
			activatedIndex--;
			if (activatedIndex < 0)
				activatedIndex = 0;
		}
		else if (Input::isPressed(KEY_RIGHT))
		{
			activatedIndex++;
			if (activatedIndex > 1)
				activatedIndex = 1;
		}
		else if (Input::isPressed(27))
		{
			this->helpWin->borders(Window::BORDER_NONE);
			this->helpWin->clear();
			this->helpWin->refresh();
			return;
		}
	}
}

std::string WindowStatistic::toString(int num)
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
void WindowStatistic::createHistory()
{
	historyMenu = new Menu(1, 1, this->history->getW() - 2, this->history->getH() - 2);

	MenuItem* item;

	for (unsigned int i = 0; i < this->listInfos.size(); ++i)
	{
		item = new MenuItem(this->listInfos[i], i + 100);
		historyMenu->add(item);
	}

}
std::string WindowStatistic::getName(std::string name)
{
	std::string tmp = "";
	for (unsigned int i = 0; i < name.length(); ++i)
	{
		if (name[i] != ' ') {
			tmp += name[i];
		} else break;
	}
	return tmp;
}
std::string WindowStatistic::getGameShow()
{
	return this->show;
}
