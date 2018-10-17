#ifndef GAMESTATEGAME_H_DEFINED
#define GAMESTATEGAME_H_DEFINED

#include <Engine/GameState.hpp>
#include <Entities/Game.hpp>

class GameStateGame: public GameState
{
public:
	GameStateGame();
    virtual ~GameStateGame();

    void load();
    void unload();

	void update();
    void draw();

private:
	Game* game;

	bool willQuit;
};

#endif //GAMESTATEGAME_H_DEFINED
