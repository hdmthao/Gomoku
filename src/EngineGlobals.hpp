#ifndef ENGINEGLOBALS_H_DEFINED
#define ENGINEGLOBALS_H_DEFINED

#include <Display/Colors.hpp>
#include <string>

// Cài đặt cho các thông số của game.

class Board;

namespace EngineGlobals
{

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
		extern int AI;
		extern bool turnOnSound;

		void setLoadGame(std::string filegame);
		void setNamePlayer(std::string name, bool isPlayer1);
		void setSound();
		void setAi(int kind);
	};

	void init();

};

#endif //ENGINEGLOBALS_H_DEFINED
