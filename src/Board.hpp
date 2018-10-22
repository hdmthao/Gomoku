#include <Display/Window.hpp>
#include <EngineGlobals.hpp>

#include <vector>
using std::vector;


class Board
{

public:
    enum kindStone
    {
        EMPTY, X, O
    };

    enum role
    {
        PLAYER_1, PLAYER_2, BOT
    };
    struct infoBoard
    {
        int x;
        int y;
        kindStone role;
    } stone;

    int width;
    int height;
    int style;

    int currentX;
    int currentY;
    int lastX;
    int lastY;

    Board();
    ~Board();

    void setType(EngineGlobals::Board::Style _style);
    void setBoard();
    void draw(Window* win, role currentPlayer);

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    bool isCheckedForWin();

    bool update(role currentPlayer);
    vector< vector<kindStone> > board;
    vector< infoBoard > contains;
}
;
