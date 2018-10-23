#include <Board.hpp>
#include <iostream>


int dx[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int dy[8] = {0, 1, 0, -1, -1, 1, 1, -1};

Board::Board():
    width(0),
    height(0),
    style(EngineGlobals::Board::TICTACTOE)
{
    board.clear();
}
Board::~Board()
{
    board.clear();
}
void Board::setType(EngineGlobals::Board::Style _style)
{
    this->style = _style;
    switch (_style) {
        case EngineGlobals::Board::TICTACTOE:
            this->width = 3;
            this->height = 3;
            this->currentX = 2;
            this->currentY = 2;
            break;
        case EngineGlobals::Board::SMALL:
            this->width = 9;
            this->height = 9;
            this->currentX = 5;
            this->currentY = 5;
            break;
        case EngineGlobals::Board::NORMAL:
            this->width = 13;
            this->height = 13;
            this->currentX = 7;
            this->currentY = 7;
            break;
        case EngineGlobals::Board::BIG:
            this->width = 19;
            this->height = 19;
            this->currentX = 9;
            this->currentY = 9;
        default:
            break;
    }
}
void Board::setBoard()
{
    board.resize(this->height + 1);
    for (int i = 1; i <= this->height; ++i)
    {
        board[i].resize(this->width + 1);
    }
    for (int i = 1; i <= this->height; ++i)
    {
        for (int j = 1; j <= this->width; ++j)
        {
            this->board[i][j] = EMPTY;
        }
    }
}
void Board::draw(Window *win, role currentPlayer)
{
    if (this->style == EngineGlobals::Board::BIG)
    {
        int posX = 40 - (this->width * 2 + 1) / 2;
        int posY = 15 - (this->height) / 2;

        int virtualX = 0;
        int virtualY = 0;

        for (int x = 0; x < (this->width * 2 + 1); ++x)
        {
            if (x % 2 == 1)
                win->printChar('_', posX + x, posY, Colors::pair("white", "default"));
        }
        for (int y = 1; y <= (this->height); ++y)
        {
            virtualX++; virtualY = 0;
            for (int x = 0; x < (this->width * 2 + 1); ++x)
            {
                if (x % 2 == 0)
                    win->printChar('|', posX + x, posY + y, Colors::pair("white", "default"));
                else
                {
                    virtualY++;
                    if (virtualX == this->currentX && virtualY == this->currentY)
                    {
                        switch (board[this->currentX][this->currentY])
                        {
                            case EMPTY:
                                if (currentPlayer == PLAYER_1)
                                {
                                    win->printChar('X', posX + x, posY + y, true, Colors::pair("yellow", "cyan", true));
                                }
                                else
                                {
                                    win->printChar('O', posX + x, posY + y, true, Colors::pair("red", "cyan", true));
                                }
                                break;
                            case O:
                                win->printChar('O', posX + x, posY + y, Colors::pair("red", "cyan", true));
                                break;
                            case X:
                                win->printChar('X', posX + x, posY + y, Colors::pair("yellow", "cyan", true));
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    if (!contains.empty() && virtualX == contains.back().x && virtualY == contains.back().y)
                    {
                        switch(board[virtualX][virtualY])
                        {
                            case X:
                                win->printChar('X', posX + x, posY + y, Colors::pair("yellow", "blue", true));
                                break;
                            case O:
                                win->printChar('O', posX + x, posY + y, Colors::pair("red", "blue", true));
                            default:
                                break;
                        }
                    }
                    else
                    {
                        switch (board[virtualX][virtualY])
                        {
                            case EMPTY:
                                win->printChar('_', posX + x, posY + y, Colors::pair("white", "default", true));
                                break;
                            case O:
                                win->printChar('O', posX + x, posY + y, Colors::pair("red", "default", true));
                                break;
                            case X:
                                win->printChar('X', posX + x, posY + y, Colors::pair("yellow", "default", true));
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
    if (this->style == EngineGlobals::Board::NORMAL)
    {
        int posX = 40 - (this->width * 4) / 2;
        int posY = 15 - (this->height* 2 + 1) / 2;
        int virtualX = 0;
        int virtualY = 0;
        for (int y = 0; y <= this->height * 2; y++)
        {
            if (y % 2 == 0)
            {
                for (int x = 0; x <= this->width * 4; x++)
                {
                        if (x % 4 == 0)
                        {
                            win->printChar(ACS_DEGREE, posX + x, posY + y, Colors::pair("white", "default", true));
                        }
                        else
                        {
                            win->printChar(ACS_HLINE, posX + x, posY + y, Colors::pair("white", "default", true));
                        }
                }
            }
            else
            {
                virtualX++; virtualY = 0;
                for (int x = 0; x <= this->width * 4; x+=2)
                {
                    if (x % 4 == 0)
                    {
                        win->printChar(ACS_VLINE, posX + x, posY + y, Colors::pair("white", "default", true));
                    } else
                    {
                        virtualY++;
                        if (this->currentX == virtualX && this->currentY == virtualY)
                        {
                            switch (board[this->currentX][this->currentY])
                            {
                                case EMPTY:
                                    if (currentPlayer == PLAYER_1)
                                    {
                                        win->printChar('X', posX + x, posY + y, true, Colors::pair("yellow", "cyan", true));
                                    }
                                    else
                                    {
                                        win->printChar('O', posX + x, posY + y, true, Colors::pair("red", "cyan", true));
                                    }
                                    break;
                                case O:
                                    win->printChar('O', posX + x, posY + y, Colors::pair("red", "cyan", true));
                                    break;
                                case X:
                                    win->printChar('X', posX + x, posY + y, Colors::pair("yellow", "cyan", true));
                                    break;
                                default:
                                    break;
                            }
                        }
                        else
                        if (!contains.empty() && virtualX == contains.back().x && virtualY == contains.back().y)
                        {
                            switch(board[virtualX][virtualY])
                            {
                                case X:
                                    win->printChar('X', posX + x, posY + y, Colors::pair("yellow", "blue", true));
                                    break;
                                case O:
                                    win->printChar('O', posX + x, posY + y, Colors::pair("red", "blue", true));
                                default:
                                    break;
                            }
                        }
                        else
                        {
                            switch (board[virtualX][virtualY])
                            {
                                case EMPTY:
                                    break;
                                case O:
                                    win->printChar('O', posX + x, posY + y, Colors::pair("red", "default", true));
                                    break;
                                case X:
                                    win->printChar('X', posX + x, posY + y, Colors::pair("yellow", "default", true));
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
            }
        }
        return;
    }
    if (this->style == EngineGlobals::Board::SMALL)
    {
        int posX = 40 - (this->width * 4) / 2;
        int posY = 15 - (this->height* 2 + 1) / 2;
        int virtualX = 0;
        int virtualY = 0;
        for (int y = 0; y <= this->height * 2; y++)
        {
            if (y % 2 == 0)
            {
                for (int x = 0; x <= this->width * 4; x++)
                {
                        if (x % 4 == 0)
                        {
                            win->printChar('.', posX + x, posY + y, Colors::pair("black", "default"));
                        }
                        else
                        {
                            win->printChar('-', posX + x, posY + y, Colors::pair("white", "default", true));
                        }
                }
            }
            else
            {
                virtualX++; virtualY = 0;
                for (int x = 0; x <= this->width * 4; x+=2)
                {
                    if (x % 4 == 0)
                    {
                        win->printChar('|', posX + x, posY + y, Colors::pair("white", "default", true));
                    } else
                    {
                        virtualY++;
                        if (this->currentX == virtualX && this->currentY == virtualY)
                        {
                            switch (board[this->currentX][this->currentY])
                            {
                                case EMPTY:
                                    if (currentPlayer == PLAYER_1)
                                    {
                                        win->printChar('X', posX + x, posY + y, true, Colors::pair("yellow", "cyan", true));
                                    }
                                    else
                                    {
                                        win->printChar('O', posX + x, posY + y, true, Colors::pair("red", "cyan", true));
                                    }
                                    break;
                                case O:
                                    win->printChar('O', posX + x, posY + y, Colors::pair("red", "cyan", true));
                                    break;
                                case X:
                                    win->printChar('X', posX + x, posY + y, Colors::pair("yellow", "cyan", true));
                                    break;
                                default:
                                    break;
                            }
                        }
                        else
                        if (!contains.empty() && virtualX == contains.back().x && virtualY == contains.back().y)
                        {
                            switch(board[virtualX][virtualY])
                            {
                                case X:
                                    win->printChar('X', posX + x, posY + y, Colors::pair("yellow", "blue", true));
                                    break;
                                case O:
                                    win->printChar('O', posX + x, posY + y, Colors::pair("red", "blue", true));
                                default:
                                    break;
                            }
                        }
                        else
                        {
                            switch (board[virtualX][virtualY])
                            {
                                case EMPTY:
                                    break;
                                case O:
                                    win->printChar('O', posX + x, posY + y, Colors::pair("red", "default", true));
                                    break;
                                case X:
                                    win->printChar('X', posX + x, posY + y, Colors::pair("yellow", "default", true));
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
            }
        }
        return;
    }
    if (this->style == EngineGlobals::Board::TICTACTOE)
    {
        int posX = 40 - (this->width * 4 - 1) / 2;
        int posY = 15 - (this->height) / 2 - 3;

        int virtualX = 0;
        int virtualY = 0;

        for (int y = 0; y < this->height * 2 - 1; ++y)
        {
            if (y % 2 == 1) continue;
            virtualX++;
            virtualY = 0;
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
                else
                {
                    virtualY++;
                    if (this->currentX == virtualX && this->currentY == virtualY)
                    {
                        switch (board[this->currentX][this->currentY])
                        {
                            case EMPTY:
                                if (currentPlayer == PLAYER_1)
                                {
                                    win->printChar('X', posX + x, posY + y, true, Colors::pair("red", "cyan"));
                                } else
                                {
                                    win->printChar('O', posX + x, posY + y, true, Colors::pair("red", "cyan"));
                                }
                                break;
                            case X:
                                win->printChar('X', posX + x, posY + y, Colors::pair("black", "white", true));
                                break;
                            case O:
                                win->printChar('O', posX + x, posY + y, Colors::pair("white", "black", true));
                                break;
                        }
                    }
                    else if (!contains.empty() && virtualX == contains.back().x && virtualY == contains.back().y)
                    {
                        switch(board[virtualX][virtualY])
                        {
                            case X:
                                win->printChar('X', posX + x, posY + y, Colors::pair("black", "blue", true));
                                break;
                            case O:
                                win->printChar('O', posX + x, posY + y, Colors::pair("white", "blue", true));
                            default:
                                break;
                        }
                    }
                    else
                    {
                        switch (board[virtualX][virtualY])
                        {
                            case X:
                                win->printChar('X', posX + x, posY + y, Colors::pair("black", "default", true));
                                break;
                            case O:
                                win->printChar('O', posX + x, posY + y, Colors::pair("white", "default", true));
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
}
void Board::moveLeft()
{
    this->currentY = this->currentY - 1;
    if (this->currentY < 1) this->currentY = 1;
}
void Board::moveRight()
{
    this->currentY = this->currentY + 1;
    if(this->currentY > this->width) this->currentY = this->width;

}
void Board::moveUp()
{
    this->currentX = this->currentX - 1;
    if (this->currentX < 1) this->currentX = 1;
}
void Board::moveDown()
{
    this->currentX = this->currentX + 1;
    if (this->currentX > this->height) this->currentX = this->height;
}
bool Board::update(role currentPlayer)
{
    if (board[this->currentX][this->currentY] != EMPTY) return false;
    if (currentPlayer == PLAYER_1)
    {
        board[this->currentX][this->currentY] = X;
        stone.x = this->currentX;
        stone.y = this->currentY;
        stone.kind = X;
        contains.push_back(stone);
    }
    else if (currentPlayer == PLAYER_2)
    {
        board[this->currentX][this->currentY] = O;
        stone.x = this->currentX;
        stone.y = this->currentY;
        stone.kind = O;
        contains.push_back(stone);
    }
    return true;
}
bool Board::isOutOfBoard(int x, int y)
{
    if (x < 1 || x > this->height) return true;
    if (y < 1 || y > this->width) return true;
    return false;
}
void Board::searchForStone(Board::kindStone currentStone, int& count, int x, int y, int direction)
{
    if (isOutOfBoard(x, y)) return;
    if (board[x][y] == currentStone)
    {
        count++;
        Board::searchForStone(currentStone, count, x + dx[direction], y + dy[direction], direction);
    }
    return;
}

bool Board::isCheckedForWin()
{
    int principalDiagonal = 0;
    int secondaryDiagonal = 0;
    int verticalLine = 0;
    int horizontalLine = 0;
    int stoneExpected = 0;

    if (this->style == EngineGlobals::Board::TICTACTOE)
    {
        stoneExpected = 3;
    }
    else
    {
        stoneExpected = 5;
    }
    Board::searchForStone(board[this->currentX][this->currentY], principalDiagonal, this->currentX, this->currentY, 4);
    Board::searchForStone(board[this->currentX][this->currentY], principalDiagonal, this->currentX, this->currentY, 6);

    if (board[this->currentX][this->currentY] == X)
    if (principalDiagonal - 1 >= stoneExpected)
    {
        return true;
    }

    Board::searchForStone(board[this->currentX][this->currentY], verticalLine, this->currentX, this->currentY, 0);
    Board::searchForStone(board[this->currentX][this->currentY], verticalLine, this->currentX, this->currentY, 2);

    if (verticalLine - 1 >= stoneExpected)
    {
        return true;
    }

    Board::searchForStone(board[this->currentX][this->currentY], horizontalLine, this->currentX, this->currentY, 1);
    Board::searchForStone(board[this->currentX][this->currentY], horizontalLine, this->currentX, this->currentY, 3);

    if (horizontalLine - 1 >= stoneExpected)
    {
        return true;
    }

    Board::searchForStone(board[this->currentX][this->currentY], secondaryDiagonal, this->currentX, this->currentY, 5);
    Board::searchForStone(board[this->currentX][this->currentY], secondaryDiagonal, this->currentX, this->currentY, 7);

    if (secondaryDiagonal - 1 >= stoneExpected)
    {
        return true;
    }

    return false;
}
