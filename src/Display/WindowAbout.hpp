#ifndef WindowAbout_H_DEFINED
#define WindowAbout_H_DEFINED

#include <Display/Window.hpp>

#include <vector>

// Màn hình intro và credit
class WindowAbout {
public:
	WindowAbout(int screenWidth, int screenHeight);
	~WindowAbout();

	// update và in ra màn hình mọi thứ
	void run();

private:
	Window* main;

	Window* intro;
	Window* credit;
	Window* helpWin;
};

#endif //WindowAbout_H_DEFINED
