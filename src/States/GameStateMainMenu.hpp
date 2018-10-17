#ifndef GAMESTATEMAINMENU_H_DEFINED
#define GAMESTATEMAINMENU_H_DEFINED

#include <Engine/GameState.hpp>
#include <Display/Layouts/LayoutMainMenu.hpp>
#include <Engine/Graphics/Menu.hpp>
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

private:
	LayoutMainMenu* layout;

	// Menu chính
	Menu* menu;

	// màn hình about và intro
	WindowAbout* about;

	void createMainMenu();
};

#endif //GAMESTATEMAINMENU_H_DEFINED
