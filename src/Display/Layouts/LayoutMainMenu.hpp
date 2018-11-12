#ifndef LAYOUTMAINMENU_H_DEFINED
#define LAYOUTMAINMENU_H_DEFINED

#include <Display/Window.hpp>
#include <Display/Menu.hpp>
#include <Display/Animation.hpp>

class LayoutMainMenu
{
public:
	LayoutMainMenu(int width, int height);
	virtual ~LayoutMainMenu();

	void windowsInit(int width, int height);
	void windowsExit();

	// Vẽ menu chính
	void draw(Menu* menu, int isSubMenu, int cur = 1, char c1 = '_', char c2 = '_');

	void redraw();


	Window* main;
	Window* logo;
	Window* menu;
	Window* boardMenu;
	Window* nameMenu;
	Window* iconMenu;
	Window* loadMenu;
	Window* ruleMenu;
	Window* aiMenu;
	Window* helpWin;
	Window* animationwin;

	Animation* animation;
};

#endif //LAYOUTMAINMENU_H_DEFINED
