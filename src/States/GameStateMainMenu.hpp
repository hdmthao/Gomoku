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

private:
	LayoutMainMenu* layout;

	// Menu chính
	Menu* menu;
	Menu* boardMenu;

	// màn hình about và intro
	WindowAbout* about;

	void createMainMenu();
	void createBoardMenu();
};

#endif //GAMESTATEMAINMENU_H_DEFINED
