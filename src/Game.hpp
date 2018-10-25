#ifndef GAME_H_DEFINED
#define GAME_H_DEFINED

#include <string>
#include <Board.hpp>
#include <Player.hpp>

class LayoutGame;

class Game
{
	friend class LayoutGame;

public:
	Game();
	virtual ~Game();

	void start(bool isReady, int m_score1, int m_score2);

	void handleInput();
	void update();
	void draw();

	bool willQuit();
	bool isPlaying();
	bool willOver();
	int checkPlayerWin();
	void updateScore(int score1, int score2);
	bool isPlay;

	int numberOfGame;

protected:
	LayoutGame* layout;

	Board* board;
	Player* player1;
	Player* player2;

	bool isQuit;
	bool gameOver;

	Board::role currentPlayer;
};

#endif //GAME_H_DEFINED
