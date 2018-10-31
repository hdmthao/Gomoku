#ifndef ENGINEGLOBALS_H_DEFINED
#define ENGINEGLOBALS_H_DEFINED

#include <Display/Colors.hpp>
#include <string>

// Cài đặt cho các thông số của game.

class Board;

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

	namespace Board
	{
		enum Style
		{
			TICTACTOE, SMALL, NORMAL, BIG
		};
		extern Style style;
		void setGameStyle(Style _style);

	};

	namespace Game
	{
		extern std::string currentGame;
		void setLoadGame(std::string filegame);
	};

	void init();

};

#endif //ENGINEGLOBALS_H_DEFINED
