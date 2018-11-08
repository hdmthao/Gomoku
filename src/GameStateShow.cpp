#include <GameStateShow.hpp>
#include <StateManager.hpp>
#include <Input.hpp>
#include <Display/Window.hpp>
#include <StateManager.hpp>
#include <GameStateMainMenu.hpp>
#include <LoadStat.hpp>

GameStateShow::GameStateShow(string m_filename):
    filename(m_filename),
    main(NULL),
    infoBot(NULL),
    infoTop(NULL),
    scoreBoardTop(NULL),
    scoreBoardBot(NULL),
    willQuit(false),
    round(1)
{
    init();
    LoadStat::load(this->filename);
    this->numberOfRound = LoadStat::countGame;
    board.clear();
}
GameStateShow::~GameStateShow()
{
    SAFE_DELETE(this->main);
    SAFE_DELETE(this->help);
    SAFE_DELETE(this->infoTop);
    SAFE_DELETE(this->infoBot);
    SAFE_DELETE(this->scoreBoardTop);
    SAFE_DELETE(this->scoreBoardBot);

    board.clear();
}
void GameStateShow::init()
{
    clear();
    int current_height, current_width;
    getmaxyx(stdscr, current_height, current_width);

    int main_x = 0;
    int main_y = 0;

    main_x = current_width/2 - 40;

    main_y = current_height/2 - 15;

    this->main = new Window(main_x, main_y, 80, 30);
    this->main->refresh();

    this->help = new Window(130, 15, 24, 10);
    this->help->borders(Window::BORDER_FANCY);
    this->help->setTitle("Help");

    this->infoTop = new Window(130, 6, 24, 8);
    this->infoTop->borders(Window::BORDER_FANCY);

    this->infoBot = new Window(130, 26, 24, 8);
    this->infoBot->borders(Window::BORDER_FANCY);
    this->infoBot->setTitle(LoadStat::getNamePlayer(2));

    this->scoreBoardTop = new Window(this->infoTop, 10, 2, 11, 4);
    this->scoreBoardTop->borders(Window::BORDER_NONE);
    this->scoreBoardTop->setTitle("SCORE");

    this->scoreBoardBot = new Window(this->infoBot, 10, 2, 11, 4);
    this->scoreBoardBot->borders(Window::BORDER_NONE);
    this->scoreBoardBot->setTitle("SCORE");
}

void GameStateShow::load()
{
}
void GameStateShow::unload()
{
}
void GameStateShow::initRound()
{
    this->namePlayer1 = LoadStat::namePlayer1;
    this->namePlayer2 = LoadStat::namePlayer2;
    this->XIcon = LoadStat::XIcon;
    this->OIcon = LoadStat::OIcon;
    this->score1 = LoadStat::score[round - 1].first;
    this->score2 = LoadStat::score[round - 1].second;
    this->size = LoadStat::size;
    this->gameMode = LoadStat::gameMode;
    this->player1Win = true;

    this->main->setTitle(this->filename);
    this->main->setTitle(this->gameMode, Window::TOP_LEFT);
    this->main->setTitle("Round " + toString(round), Window::TOP_RIGHT);

    board.clear();
    vector< pair< pair<int, int>, int> > vec = LoadStat::board[round - 1];

    board.resize(size + 1);
    for (int i = 1; i <= size; ++i)
    {
        board[i].resize(size + 1);
    }
    for (int i = 1; i <= size; ++i)
    {
        for (int j = 1; j <= size; ++j)
        {
            board[i][j] = 0;
        }
    }
    this->isDrawGame = true;
    for (unsigned int i = 0; i < vec.size(); ++i)
    {
        pair< pair<int, int>, int> tmp;
        tmp = vec[i];
        board[tmp.first.first][tmp.first.second] = tmp.second;
        if (tmp.second == 4) this->player1Win = false;
        if (tmp.second == 4 || tmp.second == 3) this->isDrawGame = false;
    }
}
void GameStateShow::drawBoard()
{
    if (this->size == 19 || this->size == 25)
    {
        int posX = 40 - (this->size * 2 + 1) / 2;
        int posY = 15 - (this->size) / 2;

        int virtualX = 0;
        int virtualY = 0;

        for (int x = 0; x < (this->size * 2 + 1); ++x)
        {
            if (x % 2 == 1)
                this->main->printChar('_', posX + x, posY, Colors::pair("white", "default"));
        }
        for (int y = 1; y <= (this->size); ++y)
        {
            virtualX++; virtualY = 0;
            for (int x = 0; x < (this->size * 2 + 1); ++x)
            {
                if (x % 2 == 0)
                    this->main->printChar('|', posX + x, posY + y, Colors::pair("white", "default"));
                else
                {
                    virtualY++;
                        switch (board[virtualX][virtualY])
                        {
                            case 0:
                                this->main->printChar('_', posX + x, posY + y, Colors::pair("white", "default", true));
                                break;
                            case 2:
                                this->main->printChar(this->OIcon, posX + x, posY + y, Colors::pair("red", "default", true));
                                break;
                            case 1:
                                this->main->printChar(this->XIcon, posX + x, posY + y, Colors::pair("yellow", "default", true));
                                break;
                            case 3:
                                this->main->printChar(this->XIcon, posX + x, posY + y, true, Colors::pair("yellow", "blue", true));
                                break;
                            case 4:
                                this->main->printChar(this->OIcon, posX + x, posY + y, true, Colors::pair("red", "blue", true));
                                break;
                            default:
                                break;
                        }
                }
            }
        }
        return;
    }
    if (this->size == 13)
    {
        int posX = 40 - (this->size * 4) / 2;
        int posY = 15 - (this->size* 2 + 1) / 2;
        int virtualX = 0;
        int virtualY = 0;
        for (int y = 0; y <= this->size * 2; y++)
        {
            if (y % 2 == 0)
            {
                for (int x = 0; x <= this->size * 4; x++)
                {
                        if (x % 4 == 0)
                        {
                            this->main->printChar(ACS_DEGREE, posX + x, posY + y, Colors::pair("white", "default", true));
                        }
                        else
                        {
                            this->main->printChar(ACS_HLINE, posX + x, posY + y, Colors::pair("white", "default", true));
                        }
                }
            }
            else
            {
                virtualX++; virtualY = 0;
                for (int x = 0; x <= this->size * 4; x+=2)
                {
                    if (x % 4 == 0)
                    {
                        this->main->printChar(ACS_VLINE, posX + x, posY + y, Colors::pair("white", "default", true));
                    } else
                    {
                        virtualY++;
                        switch (board[virtualX][virtualY])
                        {
                            case 0:
                                break;
                            case 2:
                                this->main->printChar(this->OIcon, posX + x, posY + y, Colors::pair("red", "default", true));
                                break;
                            case 1:
                                this->main->printChar(this->XIcon, posX + x, posY + y, Colors::pair("yellow", "default", true));
                                break;
                            case 3:
                                this->main->printChar(this->XIcon, posX + x, posY + y, true, Colors::pair("yellow", "blue", true));
                                break;
                            case 4:
                                this->main->printChar(this->OIcon, posX + x, posY + y, true, Colors::pair("red", "blue", true));
                                break;

                            default:
                                break;
                        }
                    }
                }
            }
        }
        return;
    }
    if (this->size == 9)
    {
        int posX = 40 - (this->size * 4) / 2;
        int posY = 15 - (this->size* 2 + 1) / 2;
        int virtualX = 0;
        int virtualY = 0;
        for (int y = 0; y <= this->size * 2; y++)
        {
            if (y % 2 == 0)
            {
                for (int x = 0; x <= this->size * 4; x++)
                {
                        if (x % 4 == 0)
                        {
                            this->main->printChar('.', posX + x, posY + y, Colors::pair("black", "default"));
                        }
                        else
                        {
                            this->main->printChar('-', posX + x, posY + y, Colors::pair("white", "default", true));
                        }
                }
            }
            else
            {
                virtualX++; virtualY = 0;
                for (int x = 0; x <= this->size * 4; x+=2)
                {
                    if (x % 4 == 0)
                    {
                        this->main->printChar('|', posX + x, posY + y, Colors::pair("white", "default", true));
                    } else
                    {
                        virtualY++;
                        switch (board[virtualX][virtualY])
                        {
                            case 0:
                                break;
                            case 2:
                                this->main->printChar(this->OIcon, posX + x, posY + y, Colors::pair("red", "default", true));
                                break;
                            case 1:
                                this->main->printChar(this->XIcon, posX + x, posY + y, Colors::pair("yellow", "default", true));
                                break;
                            case 3:
                                this->main->printChar(this->XIcon, posX + x, posY + y, true, Colors::pair("yellow", "white", true));
                                break;
                            case 4:
                                this->main->printChar(this->OIcon, posX + x, posY + y, true, Colors::pair("red", "white", true));
                                break;

                            default:
                                break;
                        }
                    }
                }
            }
        }
        return;
    }
    if (this->size == 3)
    {
        int posX = 40 - (this->size * 4 - 1) / 2;
        int posY = 15 - (this->size) / 2 - 3;

        int virtualX = 0;
        int virtualY = 0;

        for (int y = 0; y < this->size * 2 - 1; ++y)
        {
            if (y % 2 == 1) continue;
            virtualX++;
            virtualY = 0;
            for (int x = 0; x < this->size * 4 - 1; ++x)
            {
                if (x % 4 == 3)
                {
                    this->main->printChar(' ', posX + x, posY + y);
                }
                else if (x % 2 == 0 && (x / 2) % 2 == 0)
                {
                    this->main->printChar('[', posX + x, posY + y, Colors::pair("yellow", "default"));
                }
                else if (x % 2 == 0 && (x / 2) % 2 == 1)
                {
                    this->main->printChar(']', posX + x, posY + y, Colors::pair("green", "default"));
                }
                else
                {
                    virtualY++;
                    switch (board[virtualX][virtualY])
                    {
                        case 1:
                            this->main->printChar(this->XIcon, posX + x, posY + y, Colors::pair("black", "default", true));
                            break;
                        case 2:
                            this->main->printChar(this->OIcon, posX + x, posY + y, Colors::pair("white", "default", true));
                            break;
                        case 3:
                            this->main->printChar(this->XIcon, posX + x, posY + y, true, Colors::pair("yellow", "cyan", true));
                            break;
                        case 4:
                            this->main->printChar(this->OIcon, posX + x, posY + y, true, Colors::pair("red", "cyan", true));
                            break;

                        default:
                            break;
                    }
                }
            }
        }
        return;
    }
}
void GameStateShow::update()
{
	if (this->willQuit)
		StateManager::change(new GameStateMainMenu());
    initRound();
    draw();
    Input::update(-1);
    if (Input::isPressed(27))
        this->willQuit = true;
    else if (Input::isPressed(KEY_LEFT))
    {
        round--;
        if (round < 1) round = 1;
    }
    else if (Input::isPressed(KEY_RIGHT))
    {
        round++;
        if (round > this->numberOfRound) round = this->numberOfRound;
    }

}
void GameStateShow::draw()
{
    this->main->clear();
    drawBoard();
    this->main->refresh();

    this->infoTop->setTitle(this->namePlayer1);
    this->infoBot->setTitle(this->namePlayer2);
    this->infoTop->clear();
    this->infoBot->clear();
    this->scoreBoardTop->clear();
    this->scoreBoardBot->clear();

    if (this->player1Win && !this->isDrawGame)
    {
        this->infoTop->print(Utils::String::split("#   #\n"
                                                  "  #  \n"
                                                  "#   #\n", '\n'), 2, 2, Colors::pair("cyan", "default", true));
        this->infoBot->print(Utils::String::split(" o o \n"
                                                  "o   o\n"
                                                  " o o \n", '\n'), 2, 2, Colors::pair("black", "default", true));

        this->infoTop->print(this->namePlayer1 + " WIN^^", this->infoTop->getW() / 2 - 6, 6, Colors::pair("magenta", "default", true));
        this->infoBot->print(this->namePlayer2 + " LOSE:\(", this->infoTop->getW() / 2 - 7, 6, Colors::pair("black", "default"));
    }
    else if (!this->isDrawGame)
    {
        this->infoTop->print(Utils::String::split("#   #\n"
                                                  "  #  \n"
                                                  "#   #\n", '\n'), 2, 2, Colors::pair("black", "default", true));
        this->infoBot->print(Utils::String::split(" o o \n"
                                                  "o   o\n"
                                                  " o o \n", '\n'), 2, 2, Colors::pair("cyan", "default", true));
        this->infoTop->print(this->namePlayer1 + " LOSE:\(", this->infoTop->getW() / 2 - 6, 6, Colors::pair("black", "default"));
        this->infoBot->print(this->namePlayer2 + " WIN^^", this->infoTop->getW() / 2 - 7, 6, Colors::pair("magenta", "default", true));
    }
    else
    {
        this->infoTop->print(Utils::String::split("#   #\n"
                                                  "  #  \n"
                                                  "#   #\n", '\n'), 2, 2, Colors::pair("black", "default", true));
        this->infoBot->print(Utils::String::split(" o o \n"
                                                  "o   o\n"
                                                  " o o \n", '\n'), 2, 2, Colors::pair("cyan", "default", true));
        this->infoTop->print("!!! D R A W !!!", this->infoTop->getW() / 2 - 6, 6, Colors::pair("magenta", "default", true));
        this->infoBot->print("!!! D R A W !!!", this->infoTop->getW() / 2 - 7, 6, Colors::pair("magenta", "default", true));
    }
    drawNumberTop(this->score1);
    drawNumberBot(this->score2);

    this->infoTop->refresh();
    this->infoBot->refresh();
    refresh();
}
void GameStateShow::drawNumberTop(int number)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < number; ++i)
	{
		this->scoreBoardTop->printChar(ACS_DIAMOND, 1 + x*2, 1 + y, Colors::pair("white", "default", true));
		x++;
		if (i == 4)
		{
			y++;
			x = 0;
		}
	}
}
void GameStateShow::drawNumberBot(int number)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < number; ++i)
	{
		this->scoreBoardBot->printChar(ACS_DIAMOND, 1 + x*2, 1 + y, Colors::pair("white", "default", true));
		x++;
		if (i == 4)
		{
			y++;
			x = 0;
		}
	}
}
string GameStateShow::toString(int num)
{
    if (num == 0) return "0";
    string tmp = "";
    while (num != 0)
    {
        tmp = (char)(num % 10 + '0') + tmp;
        num /= 10;
    }
    return tmp;
}
