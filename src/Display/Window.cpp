#include <Display/Window.hpp>
#include <EngineGlobals.hpp>

#include <sstream>				// stringstream
#include <iostream>

Window::Window(int x, int y, int w, int h):
	win(NULL),
	x(x),
	y(y),
	width(w),
	height(h),
	borderType(BORDER_NONE),
	centerTitle()
{
	this->win = newwin(height, width, y, x);
	this->setBorders();
}
Window::Window(Window* parent, int x, int y, int width, int height):
	win(NULL),
	borderType(BORDER_NONE),
	centerTitle("")
{
	if (parent->borderType == BORDER_NONE)
	{
		if (width  == 0) width  = parent->width;
		if (height == 0) height = parent->height;
	}
	else
	{
		if (x == 0) x = 1;
		if (y == 0) y = 1;

		if (width  == 0) width  = parent->width  - 2;
		if (height == 0) height = parent->height - 2;
	}

	this->x = x;
	this->y = y;
	this->width  = width;
	this->height = height;

	this->win = derwin(parent->win, height, width, y, x);
	if (!win)
		throw "Could not create Ncurses Window";

	this->setBorders();
}

Window::~Window()
{
	if (this->win)
		delwin(this->win);
}

void Window::print(std::string str, int x, int y, ColorPair pair)
{
	Colors::pairActivate(this->win, pair);

	if (! str.empty())
		mvwaddstr(this->win, y, x, str.c_str());
}

void Window::print(std::vector<std::string> lines, int x, int y, ColorPair pair)
{
	for (size_t i = 0; i < lines.size(); i++)
		this->print(lines[i], x, (y + i), pair);
}

void Window::printChar(int c, int x, int y, ColorPair pair)
{
	Colors::pairActivate(this->win, pair);

	mvwaddch(this->win, y, x, c);
}

void Window::setBackground(chtype ch, ColorPair pair)
{
	wbkgd(this->win, (ch | pair.ncurses_pair));
}

void Window::refresh()
{
	wnoutrefresh(this->win);
}

void Window::clear()
{
	werase(this->win);

	if (this->borderType != BORDER_NONE)
		this->borders(this->borderType);

	if (!this->centerTitle.empty())
	{
		this->print(this->centerTitle,
		            this->width/2 - this->centerTitle.size() / 2, 0,
		            Colors::pair("yellow", "default"));
	}
}

int Window::getW() const
{
	return this->width;
}
int Window::getH() const
{
	return this->height;
}
int Window::getX() const
{
	return this->x;
}
int Window::getY() const
{
	return this->y;
}
void Window::borders(BorderType type)
{
	this->borderType = type;

	if (type == Window::BORDER_NONE)
		return;

	if (type == Window::BORDER_FANCY)
	{
		wborder(this->win,
		        ACS_VLINE    | Colors::pair("red", "default", true).ncurses_pair,
		        ACS_VLINE    | Colors::pair("red", "default", true).ncurses_pair,
		        ACS_HLINE    | Colors::pair("red", "default", true).ncurses_pair,
		        ACS_HLINE    | Colors::pair("red", "default", true).ncurses_pair,
		        ACS_ULCORNER | Colors::pair("red", "default", true).ncurses_pair,
		        ACS_URCORNER | Colors::pair("red", "default", true).ncurses_pair,
		        ACS_LLCORNER | Colors::pair("red", "default", true).ncurses_pair,
		        ACS_LRCORNER | Colors::pair("red", "default", true).ncurses_pair);
	}
	else if (type == Window::BORDER_REGULAR)
	{
		ColorPair red = Colors::pair("red", "default", true);

		Colors::pairActivate(this->win, red);
		wborder(this->win, '|', '|', '-', '-', '+', '+', '+', '+');
	}
}

void Window::setBorders()
{
	this->borders(Window::BORDER_FANCY);
}

void Window::setTitle(std::string title, WindowTitlePosition position)
{
	switch (position)
	{
	case CENTER:     this->centerTitle     = title; break;
	default: return;
	}
}