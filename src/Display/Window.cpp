#include <Display/Window.hpp>
#include <EngineGlobals.hpp>

#include <sstream>				// stringstream

Window::Window(int x, int y, int w, int h):
	win(NULL),
	x(x),
	y(y),
	width(w),
	height(h),
	borderType(BORDER_NONE),
	centerTitle(""),
	leftTitle(""),
	rightTitle("")
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
void Window::print(std::string str, int x, int y, bool isAttr, ColorPair pair)
{
	Colors::pairActivate(this->win, pair);
	if (isAttr) wattron(this->win, A_BLINK);

	if (! str.empty())
		mvwaddstr(this->win, y, x, str.c_str());
	if (isAttr) wattroff(this->win, A_BLINK);
}
void Window::print(std::vector<std::string> lines, int x, int y, ColorPair pair)
{
	for (size_t i = 0; i < lines.size(); i++)
		this->print(lines[i], x, (y + i), pair);
}
void Window::print(std::vector<std::string> lines, int x, int y, bool isAttr, ColorPair pair)
{

	for (size_t i = 0; i < lines.size(); i++)
		this->print(lines[i], x, (y + i), true, pair);
}
void Window::printChar(int c, int x, int y, ColorPair pair)
{
	Colors::pairActivate(this->win, pair);

	mvwaddch(this->win, y, x, c);
}
void Window::printChar(int c, int x, int y, bool isBlink, ColorPair pair)
{
	Colors::pairActivate(this->win, pair);
	if (isBlink) wattron(this->win, A_BLINK);
	mvwaddch(this->win, y, x, c);
	if (isBlink) wattroff(this->win, A_BLINK);
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
		            Colors::pair("yellow", "default", true));
	}
	if (!this->leftTitle.empty())
	{
		this->print(this->leftTitle,
		            2, 0,
		            Colors::pair("yellow", "default", true));
	}
	if (!this->rightTitle.empty())
	{

		this->print(this->rightTitle,
		            this->getW() - 1 - this->rightTitle.size() - 1, 0,
		            Colors::pair("yellow", "default", true));
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
		ColorPair red = Colors::pair("red", "default", true);

		Colors::pairActivate(this->win, red);
		wborder(this->win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	}
	else if (type == Window::BORDER_REGULAR)
	{
		ColorPair red = Colors::pair("red", "default", true);

		Colors::pairActivate(this->win, red);
		wborder(this->win, '|', '|', '-', '-', '+', '+', '+', '+');
	}
	else if (type == Window::BORDER_GAME)
	{
		ColorPair cyan = Colors::pair("cyan", "default", true);
		Colors::pairActivate(this->win, cyan);
		wborder(this->win, ACS_PI, ACS_PI, ACS_PI, ACS_PI, ACS_PI, ACS_PI, ACS_PI, ACS_PI);
	}
	else if (type == Window::BORDER_GAME_WIN)
	{
		ColorPair cyan = Colors::pair("cyan", "default", true);
		Colors::pairActivate(this->win, cyan);
		wattron(this->win, A_BLINK);
		wborder(this->win, ACS_PI, ACS_PI, ACS_PI, ACS_PI, ACS_PI, ACS_PI, ACS_PI, ACS_PI);
		wattroff(this->win, A_BLINK);
	} else if (type == Window::BORDER_INFO)
	{
		ColorPair white = Colors::pair("white", "default");
		Colors::pairActivate(this->win, white);
		wborder(this->win, ACS_DIAMOND, ACS_DIAMOND, ACS_DIAMOND,ACS_DIAMOND,ACS_DIAMOND,ACS_DIAMOND,ACS_DIAMOND,ACS_DIAMOND);
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
	case CENTER:	this->centerTitle     = title; break;
	case TOP_LEFT:	this->leftTitle = title; break;
	case TOP_RIGHT:	this->rightTitle = title; break;
	default: return;
	}
}
