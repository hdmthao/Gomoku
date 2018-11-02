#ifndef GAMESTATEGAME_H_DEFINED
#define GAMESTATEGAME_H_DEFINED

#include <GameState.hpp>
#include <Game.hpp>
#include <string>

using std::string;

class GameStateGame: public GameState
{
public:
	GameStateGame();
    virtual ~GameStateGame();

    void load();
    void unload();

	void update();
    void draw();

	void showDialog(string, int width, int height);
	bool showRetryDialog(string, int width, int height);
private:
	Game* game;

	int score1;
	int score2;
	string namePlayer1;
	string namePlayer2;
	bool willQuit;
	bool isReady;
};

#endif //GAMESTATEGAME_H_DEFINED
