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
			TICTACTOE, SMALL, NORMAL, BIG, BIGEST
		};
		extern int XIcon;
		extern int OIcon;
		extern Style style;
		void setGameStyle(Style _style);
		void setXIcon(int icon);
		void setOIcon(int icon);
	};

	namespace Game
	{
		extern std::string currentGame;
		extern std::string namePlayer1;
		extern std::string namePlayer2;
		extern bool turnOnSound;
		void setLoadGame(std::string filegame);
		void setNamePlayer(std::string name, bool isPlayer1);
		void setSound();
	};

	void init();

};

#endif //ENGINEGLOBALS_H_DEFINED
