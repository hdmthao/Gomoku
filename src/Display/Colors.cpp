#include <Display/Colors.hpp>

Color::Color(std::string name):
	name(name),
	ncurses_color(COLOR_WHITE)
{ }


ColorPair::ColorPair():
	bold(false),
	ncurses_pair(0)
{ }

ColorPair::ColorPair(Color foreground, Color background):
	foreground(foreground),
	background(background),
	bold(false),
	ncurses_pair(0)
{ }


#define COLOR_DEFAULT -1

bool Colors::hasColors = false;

bool Colors::init()
{
	if (has_colors() != TRUE)	/* ncurses BOOL */
	{
		Colors::hasColors = false;
		return false;
	}
	Colors::hasColors = true;

	start_color();

	// #define COLOR_BLACK   0
	// #define COLOR_RED     1
	// #define COLOR_GREEN   2
	// #define COLOR_YELLOW  3
	// #define COLOR_BLUE    4
	// #define COLOR_MAGENTA 5
	// #define COLOR_CYAN    6
	// #define COLOR_WHITE   7

	int i, j, k = 1;
	for (i = COLOR_BLACK; i <= COLOR_WHITE; i++)
	{
		for (j = COLOR_BLACK; j <= COLOR_WHITE; j++)
		{
			init_pair(k, i, j);
			k++;
		}
	}

	if (use_default_colors() != ERR)
	{
		// default background
		init_pair(64, COLOR_BLACK,   COLOR_DEFAULT);
		init_pair(65, COLOR_RED,     COLOR_DEFAULT);
		init_pair(66, COLOR_GREEN,   COLOR_DEFAULT);
		init_pair(67, COLOR_YELLOW,  COLOR_DEFAULT);
		init_pair(68, COLOR_BLUE,    COLOR_DEFAULT);
		init_pair(69, COLOR_MAGENTA, COLOR_DEFAULT);
		init_pair(70, COLOR_CYAN,    COLOR_DEFAULT);
		init_pair(71, COLOR_WHITE,   COLOR_DEFAULT);
	}
	return true;
}


ColorPair Colors::pair(Color& foreground, Color& background, bool is_bold)
{
	ColorPair pair(foreground, background);
	if (is_bold)
		pair.bold = true;

	short fg = foreground.ncurses_color;
	
	if (is_bold) pair.ncurses_pair = COLOR_PAIR(64 + fg) | A_BOLD;
	else pair.ncurses_pair = COLOR_PAIR(64 + fg);

	return pair;
}

Color Colors::name(std::string str)
{
	Color color;

	if (str.empty())
		return color;

	     if (str == "default") color.ncurses_color = COLOR_DEFAULT;
	else if (str == "black")   color.ncurses_color = COLOR_BLACK;
	else if (str == "red")     color.ncurses_color = COLOR_RED;
	else if (str == "green")   color.ncurses_color = COLOR_GREEN;
	else if (str == "yellow")  color.ncurses_color = COLOR_YELLOW;
	else if (str == "blue")    color.ncurses_color = COLOR_BLUE;
	else if (str == "magenta") color.ncurses_color = COLOR_MAGENTA;
	else if (str == "cyan")    color.ncurses_color = COLOR_CYAN;
	else if (str == "white")   color.ncurses_color = COLOR_WHITE;

	color.name = str;
	return color;
}

ColorPair Colors::pair(std::string foreground, std::string background, bool is_bold)
{
	if (foreground.empty() || background.empty())
		return ColorPair();

	Color f = Colors::name(foreground);
	Color b = Colors::name(background);

	return Colors::pair(f, b, is_bold);
}

void Colors::activate(WINDOW* window, Color& foreground, Color& background)
{
	ColorPair pair = Colors::pair(foreground, background);

	Colors::pairActivate(window, pair);
}

void Colors::pairActivate(WINDOW* window, ColorPair& color)
{
	wattrset(window, color.ncurses_pair);
}
