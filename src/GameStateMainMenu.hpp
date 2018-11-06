#ifndef GAMESTATEMAINMENU_H_DEFINED
#define GAMESTATEMAINMENU_H_DEFINED

#include <GameState.hpp>
#include <Display/Layouts/LayoutMainMenu.hpp>
#include <Display/Menu.hpp>
#include <Display/WindowAbout.hpp>
#include <Display/WindowStatistic.hpp>

// Trạng thái menu

class GameStateMainMenu: public GameState
{
	friend class LayoutMainMenu;

public:
	GameStateMainMenu();
	virtual ~GameStateMainMenu() { };

    void load();
    void unload();

	void update();
    void draw();
	bool isActivatedPVP;
	bool isActivatedLOAD;
	bool isActivatedName1;
	bool isActivatedName2;
	bool isActivateSetting;

private:
	LayoutMainMenu* layout;

	// Menu chính
	Menu* menu;
	Menu* boardMenu;
	Menu* marvelMenu;
	Menu* mobaMenu;
	Menu* loadMenu;
	Menu* settingMenu;

	// màn hình about và intro
	WindowAbout* about;
	WindowStatistic* statistic;

	void createMainMenu();
	void createBoardMenu();
	void createMarvelMenu();
	void createMobaMenu();
	void createLoadMenu();
	void createSettingMenu();
};

#endif //GAMESTATEMAINMENU_H_DEFINED
