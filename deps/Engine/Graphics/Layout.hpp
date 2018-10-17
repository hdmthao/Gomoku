#ifndef LAYOUT_H_DEFINED
#define LAYOUT_H_DEFINED

#include <Engine/Graphics/Window.hpp>

class Layout
{
public:
	Layout(int width, int height);
	virtual ~Layout();

	virtual void windowsInit();
	virtual void windowsExit();

	virtual void draw();

	Window* main;
};

#endif //LAYOUT_H_DEFINED
