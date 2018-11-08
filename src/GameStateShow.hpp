#ifndef GAMESTATESHOW_H_DEFINED
#define GAMESTATESHOW_H_DEFINED

#include <GameState.hpp>
#include <Game.hpp>
#include <string>
#include <Display/Window.hpp>

using std::string;
using std::pair;
using std::vector;

class GameStateShow: public GameState
{
public:
	GameStateShow(string m_filename);
    virtual ~GameStateShow();

    void load();
    void unload();

	void update();
    void draw();

    void init();
	void initRound();
	void drawBoard();
	void drawNumberTop(int number);
	void drawNumberBot(int number);
	string toString(int num);

private:

    Window* main;
    Window* help;
    Window* infoTop;
    Window* infoBot;
    Window* scoreBoardTop;
    Window* scoreBoardBot;

	string filename;
    int numberOfRound;
    int round;
	int size;
	bool player1Win;
	bool isDrawGame;
	int score1;
	int score2;
	string namePlayer1;
	string namePlayer2;
	int XIcon;
	int OIcon;
	string gameMode;

	vector<vector<int>> board;

    bool willQuit;
};

#endif //GameStateShow_H_DEFINED
