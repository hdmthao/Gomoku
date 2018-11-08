#include <EngineGlobals.hpp>


EngineGlobals::Board::Style EngineGlobals::Board::style;
int EngineGlobals::Board::XIcon;
int EngineGlobals::Board::OIcon;

std::string EngineGlobals::Game::currentGame;
std::string EngineGlobals::Game::namePlayer1;
std::string EngineGlobals::Game::namePlayer2;
int EngineGlobals::Game::AI;
bool EngineGlobals::Game::turnOnSound;

void EngineGlobals::init()
{
	EngineGlobals::Board::style = EngineGlobals::Board::NORMAL;
	EngineGlobals::Board::XIcon = 88;
	EngineGlobals::Board::OIcon = 79;

	EngineGlobals::Game::currentGame = "";
	EngineGlobals::Game::namePlayer1 = "";
	EngineGlobals::Game::namePlayer2 = "";
	EngineGlobals::Game::AI = 0;
	EngineGlobals::Game::turnOnSound = true;
}
void EngineGlobals::Board::setGameStyle(EngineGlobals::Board::Style _style)
{
	EngineGlobals::Board::style = _style;
}
void EngineGlobals::Board::setXIcon(int icon)
{
	EngineGlobals::Board::XIcon = icon;
}
void EngineGlobals::Board::setOIcon(int icon)
{
	EngineGlobals::Board::OIcon = icon;
}
void EngineGlobals::Game::setLoadGame(std::string filegame)
{
	std::string tmp = "";
	for (unsigned int i = 0; i < filegame.length(); ++i) {
		if (filegame[i] == ' ') break;
		tmp += filegame[i];
	}
	EngineGlobals::Game::currentGame = tmp;
}
void EngineGlobals::Game::setAi(int kind)
{
	EngineGlobals::Game::AI = kind;
}
void EngineGlobals::Game::setNamePlayer(std::string name, bool isPlayer1)
{
	if (isPlayer1) EngineGlobals::Game::namePlayer1 = name;
	else EngineGlobals::Game::namePlayer2 = name;
}
void EngineGlobals::Game::setSound()
{
	EngineGlobals::Game::turnOnSound = !EngineGlobals::Game::turnOnSound;
}
