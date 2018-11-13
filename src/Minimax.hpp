#ifndef MINIMAX_H_DEFINED
#define MINIMAX_H_DEFINED

#include <vector>

using std::vector;
using std::pair;
using std::make_pair;

#define Position pair<int, int>
#define PositionAndScore pair< pair<int, int>, long long>
#define ROW first
#define COL second

class Minimax
{
public:
    Minimax();
    ~Minimax();

    void setDepth(int depth);
    void parse(int x, int y);
    void setSize(int size);
    void setBoard(bool willLoad);

    vector< PositionAndScore > getMovesWithScores();

    void findMoves(bool checkRow, bool checkCol, bool checkDiag, Position lastMove);
    void findLeftDiagonal(Position position);
    void findRightDiagonal(Position position);
    void findRow(Position position);
    void findColumn(Position position);
    void scoreMoves(vector<Position> moves, int score, bool isPlayer);
    bool isOutOfBoard(Position position);

    Position makeMove();
    vector<PositionAndScore> getMoves(int currentPlayer);
    PositionAndScore decideMove(int depth);
    long long minimiseMove(int depth, long long alpha, long long beta, PositionAndScore takenMove );
    long long maximiseMove(int depth, long long alpha, long long beta, PositionAndScore takenMove);
    long long scoreState(int winner, int depth, PositionAndScore takenMove);
    PositionAndScore getBestSoFar();
    void setFinished();

    int checkWinner();
    bool checkLeftDiagonals();
    bool checkRightDiagonals();
    bool checkRows();
    bool checkColumns();
    bool findWinner(bool checkRow, bool checkCol, bool checkDiag);

private:
    PositionAndScore best;
    Position lastMove;
    int depth;
    int depthCompare;
    int size;
    int currentPlayer;
    int counters;
    int maxCounters;
    long long oo;
    bool finished;

    vector< vector<int> > board;
    vector< PositionAndScore > scoredMoves;
    vector< Position > possibleMoves;
};
#endif
