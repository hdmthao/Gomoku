#include <map>
#include <algorithm>
#include <utility>

#include <Mcts.hpp>
#include <LoadGame.hpp>
#include <iostream>

Mcts::Mcts()
{
  board.clear();

}
Mcts::~Mcts()
{
  board.clear();

}
void Mcts::setSize(int size)
{
    this->size = size;
}
void Mcts::setBoard(bool willLoad)
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
void Mcts::parse(int x, int y)
{
    board[x][y] = 1;
}

vector <long long> Mcts::check(int px, int py, int icon_) {
    const int _x = px, _y = py;
    int stat[10] = {0};
    int l = 0, r = 0, i, j;

    //row
    for (i = _x - 1; i && board[i][_y] == icon_; --i) l++;
    stat[1] = i > 0 && board[i][_y] == 0;

    for (i = _x + 1; i <= this->size && board[i][_y] == icon_; ++i) r++;
    stat[1] += i <= this->size && board[i][_y] == 0;

    stat[0] = l + r + 1;

    //col
    l = 0; r = 0;
    for (i = _y - 1; i && board[_x][i] == icon_; --i) l++;
    stat[3] = i > 0 && board[_x][i] == 0;

    for (i = _y + 1; i <= this->size && board[_x][i] == icon_; ++i) r++;
    stat[3] += i <= this->size && board[_x][i] == 0;

    stat[2] = l + r + 1;

    //diagonal
    l = 0; r = 0;
    for (i = _x - 1, j = _y - 1; i && j && board[i][j] == icon_; --i, --j) l++;
    stat[5] = i > 0 && j > 0 && board[i][j] == 0;

    for (i = _x + 1, j = _y + 1; i <= this->size && j <= this->size && board[i][j] == icon_; ++i, ++j) r++;
    stat[5] += i <= this->size && j <= this->size && board[i][j] == 0;

    stat[4] = l + r + 1;

    //anti diagonal
    l = 0; r = 0;
    for (i = _x - 1, j = _y + 1; i && j <= this->size && board[i][j] == icon_; --i, ++j) l++;
    stat[7] = i && j <= this->size && board[i][j] == 0;

    for (i = _x + 1, j = _y - 1; i <= this->size && j && board[i][j] == icon_; ++i, --j) r++;
    stat[7] += i <= this->size && j && board[i][j] == 0;

    stat[6] = l + r + 1;

    //result
    vector <long long> result(6, 0);
    for (int ii = 0; ii < 8; ii += 2) {
        result[0] += (stat[ii] >= 5);
        result[1] += stat[ii] == 4 && stat[ii + 1] == 2;
        result[2] += stat[ii] == 4 && stat[ii + 1] == 1;
        result[3] += stat[ii] == 3 && stat[ii + 1] == 2;
        result[4] += stat[ii] == 3 && stat[ii + 1] == 1;
        /**/result[5] += stat[ii] == 2 && stat[ii + 1] == 2;
    }
    return result;
}

Position Mcts::getMove() {
    std::map <long long, Position, std::greater<long long> > weight;
    vector < Position > lists;

    for (int i = 1; i <= this->size; ++i) for (int j = 1; j <= this->size; ++j) if (board[i][j] == 0) {
        std::vector <long long> pointBot = check(i, j, 2);
        std::vector <long long> pointHuman = check(i, j, 1);

        long long a = pointBot[0] * 87654321 + pointHuman[0] * 7654321 + pointBot[1] * 654321 + pointHuman[1] * 654321 + pointBot[2] * 54321 + pointHuman[2] * 321 + pointBot[3] * 4321;
        if (a > 0) {
            long long b = pointHuman[3] * 3 + pointBot[4] * 5 + pointBot[5] * 5 + pointHuman[4] * 1 + pointHuman[5] * 4;
            weight[a + b] = std::make_pair(i, j);
        }
    }
    for (auto it : weight) lists.push_back(it.second);

    if (!lists.empty()) return lists[0];

    for (int i = 1; i <= this->size; ++i) for (int j = 1; j <= this->size; ++j) if (board[i][j] == 0) {
        bool ok = false;
        ok |= i > 1 && board[i - 1][j] != 0;
        ok |= j > 1 && board[i][j - 1] != 0;
        ok |= i < this->size && board[i + 1][j] != 0;
        ok |= j < this->size && board[i][j + 1] != 0;
        ok |= i > 1 && j > 1 && board[i - 1][j - 1] != 0;
        ok |= i > 1 && j < this->size && board[i - 1][j + 1] != 0;
        ok |= i < this->size && j > 1 && board[i + 1][j - 1] != 0;
        ok |= i < this->size && j < this->size && board[i  + 1][j + 1] != 0;

        if (ok == true) lists.push_back(std::make_pair(i, j));
    }
    if (!lists.empty()) return lists[0 + rand() % (lists.size())];

    int x, y;
    do {
        x = 1 + rand() % this->size;
        y = 1 + rand() % this->size;
    } while (board[x][y] != 0);
    return Position(x, y);
}

Position Mcts::makeMove() {
    Position move = getMove();
    board[move.ROW][move.COL] = 2;

    return move;
}
