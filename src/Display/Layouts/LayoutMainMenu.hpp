#ifndef LAYOUTMAINMENU_H_DEFINED
#define LAYOUTMAINMENU_H_DEFINED

#include <Engine/Graphics/Window.hpp>
#include <Engine/Graphics/Menu.hpp>
#include <Display/Animation.hpp>

class LayoutMainMenu
{
public:
	LayoutMainMenu(int width, int height);
	virtual ~LayoutMainMenu();

	void windowsInit(int width, int height);
	void windowsExit();

	// Vẽ menu chính
	void draw(Menu* menu);

	void redraw();


	Window* main;
	Window* logo;
	Window* menu;
	Window* animationwin;

	Animation* animation;
};

#endif //LAYOUTMAINMENU_H_DEFINED
