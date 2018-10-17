#ifndef ENGINEGLOBALS_H_DEFINED
#define ENGINEGLOBALS_H_DEFINED

#include <Display/Colors.hpp>

// Cài đặt cho các thông số của game.

namespace EngineGlobals
{
	namespace Screen
	{
		extern bool show_borders;
		extern bool fancy_borders;
		extern bool outer_border;
	};

	namespace Theme
	{
		extern ColorPair text;
		extern ColorPair hilite_text;
		extern ColorPair textbox;
	};

	void init();
};

#endif //ENGINEGLOBALS_H_DEFINED
