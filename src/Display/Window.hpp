#ifndef WINDOW_H_DEFINED
#define WINDOW_H_DEFINED

#include <string>
#include <vector>
#include <ncurses.h>

#include <Display/Colors.hpp>

#define WINDOW_FILL 0

class Window
{
public:
	enum BorderType
	{
		BORDER_NONE, BORDER_REGULAR, BORDER_FANCY, BORDER_GAME, BORDER_GAME_WIN
	};

	Window(int x, int y, int w, int h);

	Window(Window* parent, int x, int y, int width, int height);

	virtual ~Window();

	// in ra màn hình
	void print(std::string str, int x, int y, ColorPair pair=ColorPair());
	void print(std::string str, int x, int y, bool isAttr, ColorPair pair=ColorPair());
	void print(std::vector<std::string> lines, int x, int y, ColorPair pair=ColorPair());
	void printChar(int c, int x, int y, ColorPair pair=ColorPair());
	void printChar(int c, int x, int y, bool isBlink, ColorPair pair=ColorPair());
	void setBackground(chtype ch, ColorPair pair);

	void refresh();

	void clear();

	int getW() const;
	int getH() const;
	int getX() const;
	int getY() const;

	// vẽ border cho win.
	void borders(BorderType type);

	// set border cho win. Mặc định là fancy
	void setBorders();

	// vị trí của title trên win
	enum WindowTitlePosition
	{
		TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, CENTER
	};

	// Set title cho win
	void setTitle(std::string title, WindowTitlePosition position=Window::CENTER);

protected:

	WINDOW* win;

	int x;
	int y;
	int width;
	int height;

	BorderType borderType;

	std::string centerTitle;
};

#endif //WINDOW_H_DEFINED
