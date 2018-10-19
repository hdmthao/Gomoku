#include <Display/Window.hpp>
#include <EngineGlobals.hpp>

#include <vector>

using namespace std;

class Board
{

public:
    int width;
    int height;
    int style;

    Board();
    ~Board();

    void setType(EngineGlobals::Board::Style _style);
    void draw(Window* win);
};
