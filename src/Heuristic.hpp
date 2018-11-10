#ifndef HEURISTIC_H_DEFINDED
#define HEURISTIC_H_DEFINDED

#include <vector>

using std::vector;
using std::pair;
using std::make_pair;

#define Position pair<int, int>
#define PositionAndScore pair< pair<int, int>, int>

#define ROW first
#define COL second

class Heuristic
{
public:
    Heuristic();
    ~Heuristic();

    void setSize(int size);
    void setBoard(bool willLoad);

    pair<int, int> makeMove();
    void parse(int x, int y);

    vector< PositionAndScore > getMovesWithScores();

    void findMoves(bool checkRow, bool checkCol, bool checkDiag, Position lastMove);
    void findLeftDiagonal(Position position);
    void findRightDiagonal(Position position);
    void findRow(Position position);
    void findColumn(Position position);
    void scoreMoves(vector<Position> moves, int score, bool isPlayer);
    Position getBest();

    bool isOutOfBoard(Position position);
    
private:
    vector< vector<int> > board;
    vector<PositionAndScore> scoredMoves;
    vector<Position> possibleMoves;

    int size;
};
#endif
