#ifndef WINDOWSTATISTIC_H_DEFINED
#define WINDOWSTATISTIC_H_DEFINED

#include <Display/Window.hpp>
#include <Display/Menu.hpp>

#include <string>
#include <vector>

class WindowStatistic {
public:
	WindowStatistic(int screenWidth, int screenHeight);
	~WindowStatistic();

    void load();

	void run();

	void createHistory();

	std::string getGameShow();

private:
	Window* main;

	Window* stats;
	Window* history;
	Window* helpWin;
	Menu* historyMenu;

	std::string show;

	std::string getName(std::string name);

    int rating;
    int playedGameMul;
    int playedGameCamp;
    int winGame;
	std::string topCharacterMarvel;
	std::string topCharacterMoba;

	std::vector<std::string> listInfos;
    std::string winRate;
    std::string role;
    std::string toString(int num);
};

#endif
