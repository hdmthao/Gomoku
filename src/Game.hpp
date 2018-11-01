#ifndef GAME_H_DEFINED
#define GAME_H_DEFINED

#include <string>
#include <Board.hpp>
#include <Player.hpp>
#include <Display/Menu.hpp>

class LayoutGame;

class Game
{
	friend class LayoutGame;

public:
	Game();
	virtual ~Game();

	void start(bool isReady, int m_score1, int m_score2, bool willLoad);

	void handleInput();
	void update();
	void draw();

	bool willQuit();
	bool isPlaying();
	bool willOver();
	void swapRole();
	int checkPlayerWin();
	void updateScore(int score1, int score2);
	bool isPlay;
	bool isPause;
	void pause(bool option);

	void saveGame();

	int numberOfGame;

protected:
	LayoutGame* layout;

	Board* board;
	Player* player1;
	Player* player2;
	Menu* pauseMenu;

	bool isQuit;
	bool gameOver;
	bool userAskedToSaveGame;

	Board::role currentPlayer;
	std::string filename;
};

#endif //GAME_H_DEFINED
