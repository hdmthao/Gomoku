#ifndef GAME_H_DEFINED
#define GAME_H_DEFINED

#include <string>
#include <vector>
#include <Board.hpp>
#include <Player.hpp>
#include <Display/Menu.hpp>
#include <SFML/Audio.hpp>

using std::string;

class LayoutGame;

class Game
{
	friend class LayoutGame;

public:
	Game();
	virtual ~Game();

	void start(bool isReady, int m_score1, int m_score2, string namePlayer1, string namePlayer2, bool willLoad, bool aiMod);

	void handleInput();
	void update();
	void draw();

	bool willQuit();
	bool isPlaying();
	bool willOver();
	bool willDraw();
	void swapRole();
	int checkPlayerWin();
	void updateScore(int score1, int score2);
	bool isPlay;
	bool isPause;
	int round;
	int countTurn;
	bool isAi;
	void pause(bool option);

	void saveGame();

	std::vector< std::pair<int, int> > getLastBoard();
	int getSize();
	
	int numberOfGame;

	sf::SoundBuffer bufferX;
	sf::SoundBuffer bufferO;
	sf::SoundBuffer bufferErr;

	sf::Sound* soundX;
	sf::Sound* soundO;
	sf::Sound* soundErr;

	void turnOnSound(int cur);

protected:
	LayoutGame* layout;

	Board* board;
	Player* player1;
	Player* player2;
	Menu* pauseMenu;

	bool isQuit;
	bool gameOver;
	bool gameDraw;
	bool userAskedToSaveGame;

	Board::role currentPlayer;
	std::string filename;
};

#endif //GAME_H_DEFINED
