#include <EAI.hpp>
#include <LoadGame.hpp>
#include <unistd.h>
#include <iostream>
#include <algorithm>

int dxx[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int dyy[8] = {0, 1, 0, -1, -1, 1, 1, -1};
int strategy[21][10] =
{
    // 4 con -> win0
    { 0, 0, 2, 2, 2, 2, -1, -1, -1, -1 }, //".OOOO"0
    { 1, 2, 0, 2, 2, 2, -1, -1, -1, -1 }, //"O.OOO"1
    { 2, 2, 2, 0, 2, 2, -1, -1, -1, -1 }, //"OO.OO"2

    // doi phuong co 4 con -> chan
    { 0, 0, 1, 1, 1, 1, -1, -1, -1, -1 }, //".XXXX"0
    { 1, 1, 0, 1, 1, 1, -1, -1, -1, -1 }, //"X.XXX"1
    { 2, 1, 1, 0, 1, 1, -1, -1, -1, -1 }, //"XX.XX"2

    // 3 con -> 4 con
    { 0, 0, 2, 2, 2, 0, -1, -1, -1, -1 }, //".OOO."0
    { 2, 0, 2, 0, 2, 2, -1, -1, -1, -1 }, //".O.OO"2
    { 1, 2, 0, 2, 2, 0, -1, -1, -1, -1 }, //"O.OO."1
    { 1, 0, 0, 2, 2, 2, -1, -1, -1, -1 }, //"..OOO"1

    // doi phuong co 3 con -> chan
    { 0, 0, 1, 1, 1, 0, -1, -1, -1, -1 }, //".XXX."0
    { 1, 1, 0, 1, 1, 0, -1, -1, -1, -1 }, //"X.XX."1
    { 1, 0, 1, 0, 1, 1, -1 - 1, -1, -1 }, //".X.XX"2

    // hai con -> 3 con
    { 2, 0, 2, 0, 2, 0, -1, -1, -1, -1 }, //".O.O."2
    { 1, 0, 0, 2, 2, 0, -1, -1, -1, -1 }, //"..OO."1
    { 1, 0, 0, 2, 2, 0, 0, -1, -1, -1 }, //"..OO.."1


    { 1, 0, 0, 2, 0, 0, -1, -1, -1, -1 }, //"..O.."1
    { 1, 0, 0, 2, 0, -1, -1, -1, -1, -1 }, //"..O."1
    { 0, 0, 2, 0, -1, -1, -1, -1, -1, -1 }, //".O."0

    { 1, 0, 0, 1, 0, -1, -1, -1, -1, -1 }, //"..X."1
    { 0, 0, 1, 0, -1, -1, -1, -1, -1, -1 }, //".X."0
};

EAI::EAI()
{
    vec.clear();
    board.clear();
    for (int i=1; i<9; ++i) vec.push_back(i);
}
EAI::~EAI()
{
    board.clear();
    vec.clear();
}

void EAI::setSize(int size)
{
    this->size = size;
}
void EAI::setBoard(bool willLoad)
{
    board.resize(this->size + 1);
    for (int i = 1; i <= this->size; ++i)
    {
        board[i].resize(this->size + 1);
    }

    if (willLoad)
    {
        vector< vector<char> > loadboard;
        loadboard = LoadGame::loadBoard();
        for (int i = 1; i <= this->size; ++i)
        {
            for (int j = 1; j <= this->size; ++j)
            {
                if (loadboard[i][j] == '1')
                    this->board[i][j] = 1;
                else if (loadboard[i][j] == '2')
                    this->board[i][j] = 2;
                else
                    this->board[i][j] = 0;
            }
        }
    } else
    {
        for (int i = 1; i <= this->size; ++i)
        {
            for (int j = 1; j <= this->size; ++j)
            {
                this->board[i][j] = 0;
            }
        }
    }
}
pair<int, int> EAI::decideMove()
{
    pair<int, int> coor;

    for (int i = 0; i < 21; ++i)
    {
        for (int x = 1; x <= this->size; ++x)
        {
            for (int y = 1; y <= this->size; ++y)
            {
                if (searchFor(x, y, i)) {
                    for (int j = 0; j < strategy[i][0]; ++j)
                    {
                        x += dxx[this->direction];
                        y += dyy[this->direction];
                    }
                    board[x][y] = 2;
                    coor = make_pair(x, y);
                    usleep(200000);
                    return coor;
                }
            }
        }
    }
    int x = rand() % this->size + 1;
    int y = rand() % this->size + 1;
    board[x][y] = 2;
    coor = make_pair(x, y);
    return coor;
}
bool EAI::searchFor(int x, int y, int i)
{
    std::random_shuffle(vec.begin(), vec.end());

    for (int j = 0; j < 8; ++j)
    {
        bool isOk = true;
        int tmpx = x;
        int tmpy = y;
        for (int k = 1 ; strategy[i][k] != -1; ++k)
        {
            if (isOutOfBoard(tmpx, tmpy)) {
                isOk = false;
                break;
            }
            if (board[tmpx][tmpy] == strategy[i][k])
            {
                tmpx += dxx[vec[j] - 1];
                tmpy += dyy[vec[j] - 1];
            }
            else {
                isOk = false;
                break;
            }
        }
        if (isOk) {
            this->direction = vec[j] - 1;
            return true;
        }
    }
    return false;
}
bool EAI::isOutOfBoard(int x, int y)
{
    if (x < 1 || y < 1 || x > this->size || y > this->size) return true;
    return false;
}
void EAI::parse(int x, int y)
{
    board[x][y] = 1;
}
