#include <Board.hpp>

Board::Board():
    width(0),
    height(0),
    style(EngineGlobals::Board::TICTACTOE)
{
}
Board::~Board()
{ }
void Board::setType(EngineGlobals::Board::Style _style)
{
    this->style = _style;
    switch (_style) {
        case EngineGlobals::Board::TICTACTOE:
            this->width = 3;
            this->height = 3;
            break;
        case EngineGlobals::Board::NORMAL:
            this->width = 13;
            this->height = 13;
            break;
        case EngineGlobals::Board::BIG:
            this->width = 19;
            this->height = 19;
        default:
            break;
    }
}
void Board::draw(Window *win)
{
    if (this->style == EngineGlobals::Board::BIG)
    {
        int posX = 40 - (this->width * 2 + 1) / 2;
        int posY = 15 - (this->height) / 2;
        for (int x = 0; x < (this->width * 2 + 1); ++x)
        {
            if (x % 2 == 1)
                win->printChar('_', posX + x, posY, Colors::pair("white", "default"));
        }
        for (int y = 1; y <= (this->height); ++y)
        {
            for (int x = 0; x < (this->width * 2 + 1); ++x)
            {
                if (x % 2 == 0)
                    win->printChar('|', posX + x, posY + y, Colors::pair("white", "default"));
                else
                    win->printChar('_', posX + x, posY + y, Colors::pair("white", "default"));
            }
        }
        return;
    }
    if (this->style == EngineGlobals::Board::NORMAL)
    {
        int posX = 40 - (this->width * 4) / 2;
        int posY = 15 - (this->height* 2 + 1) / 2;
        for (int y = 0; y <= this->height * 2; y++)
        {
            if (y % 2 == 0)
            {
                for (int x = 0; x <= this->width * 4; x++)
                {
                        if (x % 4 == 0)
                        {
                            win->printChar('.', posX + x, posY + y, Colors::pair("black", "default", true));
                        }
                        else
                        {
                            win->printChar('-', posX + x, posY + y, Colors::pair("white", "default"));
                        }
                }
            }
            else
            {
                for (int x = 0; x <= this->width * 4; x+=4)
                {
                    win->printChar('|', posX + x, posY + y, Colors::pair("white", "default"));
                }
            }
        }
        return;
    }
    if (this->style == EngineGlobals::Board::TICTACTOE)
    {
        int posX = 40 - (this->width * 4 - 1) / 2;
        int posY = 15 - (this->height) / 2 - 3;

        for (int y = 0; y < this->height * 2 - 1; ++y)
        {
            if (y % 2 == 1) continue;
            for (int x = 0; x < this->width * 4 - 1; ++x)
            {
                if (x % 4 == 3)
                {
                    win->printChar(' ', posX + x, posY + y);
                }
                else if (x % 2 == 0 && (x / 2) % 2 == 0)
                {
                    win->printChar('[', posX + x, posY + y, Colors::pair("yellow", "default"));
                }
                else if (x % 2 == 0 && (x / 2) % 2 == 1)
                {
                    win->printChar(']', posX + x, posY + y, Colors::pair("green", "default"));
                }
            }
        }
        return;
    }
}
