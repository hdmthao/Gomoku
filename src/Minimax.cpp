#include <Minimax.hpp>
#include <LoadGame.hpp>
#include <algorithm>
#include <iostream>

Minimax::Minimax()
{
    board.clear();
    scoredMoves.clear();
    possibleMoves.clear();
    oo = 10000000;
    counters = 0;
    finished = false;
}
Minimax::~Minimax()
{
    board.clear();
    scoredMoves.clear();
    possibleMoves.clear();
}
void Minimax::setDepth(int depth)
{
    this->depth = depth;
}
void Minimax::setSize(int size)
{
    this->size = size;
    maxCounters = this->size * this->size;
}
void Minimax::setBoard(bool willLoad)
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
                if (this->board[i][j] != 0) counters++;
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
void Minimax::parse(int x, int y)
{
    board[x][y] = 1;
}

Position Minimax::makeMove() {

    PositionAndScore bestMove = decideMove(this->depth);
    Position position = make_pair(bestMove.ROW.ROW, bestMove.ROW.COL);
    board[position.ROW][position.COL] = 2;
    return position;

}

vector<PositionAndScore> Minimax::getMoves(int currentPlayer) {
    // return new Heuristic(state, currentPlayer).getMovesWithScores();
    this->currentPlayer = currentPlayer;

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
        scoredMoves.push_back(make_pair(make_pair(rand() % this->size + 1, rand() % this->size + 1), 2000));
    } else
    {
        // scoredMoves.sort((PositionAndScore a, PositionAndScore b) -> int.compare(b.getScore(), a.getScore()));
        std::sort(scoredMoves.begin(), scoredMoves.end(), [&]
        (PositionAndScore x, PositionAndScore y) {
            return x.COL > y.COL;
        });
    }


    return scoredMoves;
}


PositionAndScore Minimax::decideMove(int depth) {
    // Setup the initial moves.
    depthCompare = depth;
    vector<PositionAndScore> moves = getMoves(2);

    int currentScore;
    Position currentPosition;

    best = make_pair(make_pair(-1, -1), 0);

    // I.e. this is the 'default' starting move and should be played straight away.
    if ( moves.size() == 1 && moves[0].COL == 2000 )
    {
        best = moves[0];
        return best;
    }

    for (int i = 0; i < moves.size(); ++i)
    {
        // Make the AI player first again and take this move
        // board.createMove( move.getCoordinate(), currentPlayer );

        board[moves[i].ROW.ROW][moves[i].ROW.COL] = 2;
        lastMove = make_pair(moves[i].ROW.ROW, moves[i].ROW.COL);
        counters++;
        // AI player has taken move, so simulate the other player by minimising
        currentScore = minimiseMove(depth, -oo, oo, moves[i]);
        // std::cerr << moves[i].ROW.ROW - 1 << " " << moves[i].ROW.COL - 1<< " " << moves[i].COL << " " << currentScore << " ";
        // If  better than current best, replace best!
        if (best.ROW.ROW == -1 || currentScore > best.COL) {
            best = moves[i];
            best.COL = (int) currentScore;
        }

        // Reset the move as we're done with it.
        board[moves[i].ROW.ROW][moves[i].ROW.COL] = 0;
        lastMove = make_pair(-1, -1);
        counters--;
        if ( finished ) break;

    }

    return best;

}

int Minimax::minimiseMove(int depth, int alpha, int beta, PositionAndScore takenMove ) {

    int result;
    // std::cerr << takenMove.ROW.ROW - 1<< " " << takenMove.ROW.COL - 1 << " ";

    // Check the current score
    int winner = checkWinner();

    if ( depth == 0  || finished || winner != -1) {

        // Depth has been reached or game is over so score!
        result = scoreState(winner, depth, takenMove);

    } else {

        // Get the possible moves (Scored by the heuristic for the opponent)
        result = oo;
        vector< PositionAndScore > moves = getMoves(1);


        for (int i = 0; i < moves.size(); ++i) {

            // std::cerr << moves[i].ROW.ROW - 1<< " " << moves[i].ROW.COL - 1 << " ";


            board[moves[i].ROW.ROW][moves[i].ROW.COL] = 1;
            lastMove = make_pair(moves[i].ROW.ROW, moves[i].ROW.COL);
            counters++;

            // Score the move!
            int score = maximiseMove( depth - 1, alpha, beta, moves[i] );

            // We're done with it, remove it from the board.
            board[moves[i].ROW.ROW][moves[i].ROW.COL] = 0;
            lastMove = make_pair(-1, -1);
            counters--;
            // Minimise the move score
            result = std::min(result, score);
            beta = std::min(beta, score);

            // Out of bounds so break
            if ( beta <= alpha ) {
                break;
            }

        }

    }

    return result;

}


int Minimax::maximiseMove(int depth, int alpha, int beta, PositionAndScore takenMove)
{

    int result;

    // Check the current score
    int winner = checkWinner();

    if ( depth == 0 || winner != -1 || finished ) {

        // Depth has been reached or game is over so score!
        result = scoreState(winner, depth, takenMove );

    } else {

        // Get the possible moves (Scored by the heuristic for the current player)
        result = -oo;
        vector< PositionAndScore > moves = getMoves(2);

        for (int i = 0; i < moves.size(); ++i)
        {
            // Create the move
            board[moves[i].ROW.ROW][moves[i].ROW.COL] = 2;
            lastMove = make_pair(moves[i].ROW.ROW, moves[i].ROW.COL);
            counters++;
            // Score the move
            int score = minimiseMove( depth - 1, alpha, beta, moves[i]);

            // Remove the move, we're done with it.
            board[moves[i].ROW.ROW][moves[i].ROW.COL] = 0;
            lastMove = make_pair(-1, -1);
            counters--;
            // Maximise the move score
            result = std::max(result, score);
            alpha = std::max(alpha, score);

            // Out of bounds so break
            if ( beta <= alpha ) {
                break;
            }

        }

    }

    return result;
}

int Minimax::scoreState(int winner, int depth, PositionAndScore takenMove) {

    int result;

    // If draw, score is 0. Else get the heuristic value of the move
    result = (winner == 0) ? 0 : takenMove.COL;

    // Find the depth we've travelled, used as  a sort of 'Usefulness' heuristic
    depth = depthCompare - depth;

    // If it is not draw, somebody has one so score the minimiser / maximiser accordingly + a bonus of 100
    if ( winner > 0) {
        result = (winner == 2) ? (result + 100) - depth : (result + depth) - 100;
    }
    if (takenMove.ROW.ROW == 6 && takenMove.ROW.COL == 8)
    {
        // std::cerr << result << " ";
    }
    return result;

}

// Return the best move so found, useful incase there isn't enough time to finish e.g. in IterativeDeepening
PositionAndScore Minimax::getBestSoFar()
{
    return best;
}

void Minimax::findMoves(bool checkRow, bool checkCol, bool checkDiag, Position lastMove) {

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
    scoreMoves(possibleMoves, currentScore, board[lastMove.ROW][lastMove.COL] == this->currentPlayer);
}

void Minimax::findLeftDiagonal(Position position)
{
    findMoves(true, true, false, position);
}

void Minimax::findRightDiagonal(Position position)
{
    findMoves(true, true, true, position);
}

void Minimax::findColumn(Position position)
{
    findMoves(false, true, false, position);
}

void Minimax::findRow(Position position)
{
    findMoves(true, false, false, position);
}

void Minimax::scoreMoves(vector< Position > moves, int score, bool isPlayer)
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

bool Minimax::isOutOfBoard(Position position)
{
    if (position.ROW < 1 || position.COL < 1 || position.ROW > this->size || position.COL > this->size) return true;
    return false;
}

bool Minimax::findWinner(bool checkRow, bool checkCol, bool checkDiag) {
    if (isOutOfBoard(lastMove)) return false;
    bool notFinished = true;
    Position pointer = lastMove;
    int newCol = pointer.COL;
    int newRow = pointer.ROW;
    int currentScore = 0;
    int winningScore = 5;

    while ( currentScore != winningScore ) {

        // We are moving the column value i.e. checkCol
        if ( checkCol && !checkRow ) {
            newCol = notFinished ? pointer.COL - 1 : pointer.COL + 1;
        } else if ( checkRow && !checkCol) {
            // We are moving the row value i.e.  checkRow
            newRow = notFinished ? pointer.ROW - 1 : pointer.ROW + 1;
        } else if ( checkDiag ) {
            newCol = notFinished ? pointer.COL - 1 : pointer.COL + 1;
            newRow = notFinished ? pointer.ROW - 1 : pointer.ROW + 1;
        } else {
            newCol = notFinished ? pointer.COL + 1 : pointer.COL - 1;
            newRow = notFinished ? pointer.COL - 1 : pointer.COL + 1;
        }

        // If there is a player in the position, and they are the current player, increase counter
        if ( !isOutOfBoard(pointer) &&
                board[pointer.ROW][pointer.COL] == board[lastMove.ROW][lastMove.COL] ) {

            pointer = make_pair(newCol, newRow);
            currentScore++;

        } else if ( notFinished ) {

            // Else start counting the counters on the other side of placed counter
            notFinished = false;
            int resetCol = lastMove.COL;
            int resetRow = lastMove.ROW;

            if ( checkCol && !checkRow ) {
                resetCol = resetCol + 1;
            } else if ( checkRow && !checkCol ) {
                resetRow = resetRow + 1;
            } else if ( checkDiag ) {
                resetCol = resetCol + 1;
                resetRow = resetRow + 1;
            } else {
                resetCol = resetCol - 1;
                resetRow = resetRow + 1;
            }

            pointer = make_pair(resetCol, resetRow);

        } else {

            // We are finished and currentScore has not reached winningScore
            return false;

        }

    }

    // We've reached the winning Score
    return true;

}
bool Minimax::checkColumns() {
    return findWinner(false, true, false);
}
bool Minimax::checkRows() {
    return findWinner(true, false, false);
}
bool Minimax::checkRightDiagonals() {
    return findWinner(true, true, true);
}
bool Minimax::checkLeftDiagonals() {
    return findWinner(true, true, false);
}
int Minimax::checkWinner()
{
    if ( checkRows() || checkColumns() || checkRightDiagonals() || checkLeftDiagonals() )
    {
        // One of the players have won
        return board[lastMove.ROW][lastMove.COL];
    } else if ( counters >= maxCounters )
    {
        // The players have drawn
        return 0;
    } else
    {
        return -1;
    }

}
