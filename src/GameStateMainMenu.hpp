#ifndef GAMESTATEMAINMENU_H_DEFINED
#define GAMESTATEMAINMENU_H_DEFINED

#include <GameState.hpp>
#include <Display/Layouts/LayoutMainMenu.hpp>
#include <Display/Menu.hpp>
#include <Display/WindowAbout.hpp>

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
private:
	LayoutMainMenu* layout;

	// Menu chính
	Menu* menu;
	Menu* boardMenu;
	Menu* loadMenu;
	// màn hình about và intro
	WindowAbout* about;

	void createMainMenu();
	void createBoardMenu();
	void createLoadMenu();
};

#endif //GAMESTATEMAINMENU_H_DEFINED
