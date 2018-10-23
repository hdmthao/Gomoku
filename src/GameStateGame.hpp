#ifndef GAMESTATEGAME_H_DEFINED
#define GAMESTATEGAME_H_DEFINED

#include <GameState.hpp>
#include <Game.hpp>
#include <string>

class GameStateGame: public GameState
{
public:
	GameStateGame();
    virtual ~GameStateGame();

    void load();
    void unload();

	void update();
    void draw();

	void showDialog(std::string, int width, int height);
	bool showRetryDialog(std::string, int width, int height);
private:
	Game* game;

	bool willQuit;
	bool isReady;
};

#endif //GAMESTATEGAME_H_DEFINED
