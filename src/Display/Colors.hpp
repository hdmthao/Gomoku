#ifndef COLORS_H_DEFINED
#define COLORS_H_DEFINED

#include <Helpers/Utils.hpp>

#include <ncurses.h>
#include <string>
#include <vector>

struct Color
{
	std::string name;

	short ncurses_color;

	Color(std::string name="white");

};

struct ColorPair
{
	Color foreground;
	Color background;

	bool bold;

	chtype ncurses_pair;

	ColorPair();

	ColorPair(Color foreground, Color background);
};

namespace Colors
{
	extern bool hasColors;

	bool init();

	Color name(std::string str);

	ColorPair pair(Color& foreground, Color& background, bool is_bold=false);

	ColorPair pair(std::string foreground, std::string background, bool is_bold=false);

	void activate(WINDOW* window, Color& foreground, Color& background);

	void pairActivate(WINDOW* window, ColorPair& color);
}

#endif //COLORS_H_DEFINED
