#include <Heuristic.hpp>
#include <LoadGame.hpp>
#include <unistd.h>
#include <algorithm>
#include <iostream>

Heuristic::Heuristic()
{
    board.clear();
    scoredMoves.clear();
    possibleMoves.clear();
}
Heuristic::~Heuristic()
{
    board.clear();
    scoredMoves.clear();
    possibleMoves.clear();
}
void Heuristic::setSize(int size)
{
    this->size = size;
}
void Heuristic::setBoard(bool willLoad)
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

vector<PositionAndScore> Heuristic::getMovesWithScores()
{

    scoredMoves.clear();

    for ( int i = 1; i <= this->size; i++ )
    {
        for ( int j = 1; j <= this->size; j++ )
        {
            Position position = make_pair(i, j);
            if (board[i][j] != 0)
            {
                findRow(position);
                findColumn(position);
                findLeftDiagonal(position);
                findRightDiagonal(position);

            }

        }

    }


    // If there are no moves, this insinuates nobody has played yet. So just place in the middle.
    if ( scoredMoves.size() <= 0 ) {
        scoredMoves.push_back(make_pair(make_pair(rand() % this->size + 1, rand() % this->size + 1), 100000));
    } else
    {
        // scoredMoves.sort((PositionAndScore a, PositionAndScore b) -> Double.compare(b.getScore(), a.getScore()));
        // scoreMove.sort(scoredMove.begin(), scoredMove.end(), {})
        std::sort(scoredMoves.begin(), scoredMoves.end(), [&]
        (PositionAndScore x, PositionAndScore y) {
            return x.COL > y.COL;
        });
    }


    return scoredMoves;

}

void Heuristic::findMoves(bool checkRow, bool checkCol, bool checkDiag, Position lastMove) {

    bool notFinished = true;
    Position pointer = lastMove;
    possibleMoves.clear();

    int newRow = pointer.ROW;
    int newCol = pointer.COL;

    int currentScore = 0;
    int winningScore = 5;

    while ( currentScore != winningScore )
    {
        // We are moving the column value i.e. checkCol
        if ( checkCol && !checkRow )
        {
            newCol = notFinished ? pointer.COL - 1 : pointer.COL + 1;
        } else if ( checkRow && !checkCol)
        {
            // We are moving the row value i.e.  checkRow
            newRow = notFinished ? pointer.ROW - 1 : pointer.ROW + 1;
        } else if ( checkDiag )
        {
            newRow = notFinished ? pointer.ROW - 1 : pointer.ROW + 1;
            newCol = notFinished ? pointer.COL - 1 : pointer.COL + 1;
        } else
        {
            newRow = notFinished ? pointer.ROW - 1 : pointer.ROW + 1;
            newCol = notFinished ? pointer.COL + 1 : pointer.COL - 1;
        }

        // If there is a player in the position, and they are the current player, increase counter
        if ( !isOutOfBoard(pointer) &&
                board[pointer.ROW][pointer.COL] == board[lastMove.ROW][lastMove.COL] ) {

            pointer = make_pair(newRow, newCol);
            currentScore++;


        } else if ( notFinished ) {

            if ( (pointer.ROW > 0 && pointer.ROW <= this->size) &&
                    (pointer.COL > 0 && pointer.COL <= this->size) &&
                        board[pointer.ROW][pointer.COL] == 0) {
                possibleMoves.push_back(pointer);
            }

            notFinished = false;
            int resetRow = lastMove.ROW;
            int resetCol = lastMove.COL;

            if ( checkCol && !checkRow )
            {
                resetCol = resetCol + 1;
            } else if ( checkRow && !checkCol )
            {
                resetRow = resetRow + 1;
            } else if ( checkDiag )
            {
                resetCol = resetCol + 1;
                resetRow = resetRow + 1;
            } else
            {
                resetCol = resetCol - 1;
                resetRow = resetRow + 1;
            }
            pointer = make_pair(resetRow, resetCol);
        } else {

            if ( (pointer.ROW > 0 && pointer.ROW <= this->size) &&
                    (pointer.COL > 0 && pointer.COL <= this->size) &&
                        board[pointer.ROW][pointer.COL] == 0) {
                possibleMoves.push_back(make_pair(pointer.ROW, pointer.COL));
            }

            break;
        }

    }

    // Passes the possible moves, the score for those moves, and whether or not this is for the current player
    scoreMoves(possibleMoves, currentScore, board[lastMove.ROW][lastMove.COL] == 2);
}

void Heuristic::findLeftDiagonal(Position position)
{
    findMoves(true, true, false, position);
}

void Heuristic::findRightDiagonal(Position position)
{
    findMoves(true, true, true, position);
}

void Heuristic::findColumn(Position position)
{
    findMoves(false, true, false, position);
}

void Heuristic::findRow(Position position)
{
    findMoves(true, false, false, position);
}

void Heuristic::scoreMoves(vector< Position > moves, int score, bool isPlayer)
{

    for(unsigned int i = 0; i < moves.size(); ++i)
    {

        bool added = false;

        for (unsigned int j = 0; j < scoredMoves.size(); ++j)
        {

            if (moves[i].ROW == scoredMoves[j].ROW.ROW && moves[i].COL == scoredMoves[j].ROW.COL)
            {
                if (isPlayer)
                {
                    scoredMoves[j].COL += score;
                }
                else
                {
                    scoredMoves[j].COL -= score;
                }
                added = true;
                break;

            }

        }

            if ( !added  ) {
                scoredMoves.push_back(make_pair(make_pair(moves[i].ROW, moves[i].COL), (isPlayer ? score : -score)));
            }

        }

}

Position Heuristic::getBest()
{
    int score;
    int max = -1000000009;
    Position bestMove;

    for(unsigned int i = 0; i < scoredMoves.size(); ++i)
    {
        score = scoredMoves[i].COL;
        if (score < 0) score = -score;
        if(max < score) {
            max = score;
            bestMove = make_pair(scoredMoves[i].ROW.ROW, scoredMoves[i].ROW.COL);
        }

    }

    return bestMove;
}

Position Heuristic::makeMove()
{
    getMovesWithScores();

    Position bestMove = getBest();
    board[bestMove.ROW][bestMove.COL] = 2;
    usleep(100000);
    return bestMove;
}
void Heuristic::parse(int x, int y)
{
    board[x][y] = 1;
}
bool Heuristic::isOutOfBoard(Position position)
{
    if (position.ROW < 1 || position.COL < 1 || position.ROW > this->size || position.COL > this->size) return true;
    return false;
}
