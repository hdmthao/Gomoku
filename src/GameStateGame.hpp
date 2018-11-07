#ifndef GAMESTATEGAME_H_DEFINED
#define GAMESTATEGAME_H_DEFINED

#include <GameState.hpp>
#include <Game.hpp>
#include <string>
#include <vector>
#include <SFML/Audio.hpp>

using std::string;
using std::vector;
using std::pair;

class GameStateGame: public GameState
{
public:
	GameStateGame(bool aiMod);
    virtual ~GameStateGame();

    void load();
    void unload();

	void update();
    void draw();

	void showDialog(string, int width, int height);
	bool showRetryDialog(string, int width, int height);

	void saveHistory();

	sf::Music* sound;
	sf::Music* soundWin;
	sf::Music* soundDraw;

private:
	Game* game;

	int score1;
	int score2;
	string namePlayer1;
	string namePlayer2;
	bool willQuit;
	bool isReady;
	bool isAi;

	string filename;
	int countGame;
	vector<pair<int, int>> vecScore;
	vector< vector< pair<int, int> > > vecBoard;
};

#endif //GAMESTATEGAME_H_DEFINED
