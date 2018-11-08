#ifndef EAI_H_DEFINED
#define EAI_H_DEFINED

#include <Helpers/Timer.hpp>
#include <vector>

using std::pair;
using std::make_pair;
using std::vector;

class EAI
{
public:
    EAI();
    ~EAI();

    int size;

    void setSize(int size);
    void setBoard(bool willLoad);
    pair<int, int> decideMove();
    void parse(int x, int y);

    int direction;
    bool isOutOfBoard(int x, int y);
    bool searchFor(int x, int y, int i);

    vector< vector<int> > board;
    vector<int> vec;
    Timer timer;
};
#endif
