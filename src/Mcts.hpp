#ifndef MCTS_H_DEFINED
#define MCTS_H_DEFINED

#include <vector>
#include <map>

using std::vector;
using std::pair;
using std::make_pair;

#define Position pair<int, int>
#define ROW first
#define COL second

class Mcts {
public:
  Mcts();
  ~Mcts();

  void setSize(int size);
  void setBoard(bool willLoad);
  void parse(int x, int y);
  vector <long long> check(int px, int py, int icon_);

  Position getMove();
  Position makeMove();

private:

  int size;

  vector< vector<int> > board;
};
#endif
