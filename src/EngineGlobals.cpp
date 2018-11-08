#include <EngineGlobals.hpp>

ColorPair EngineGlobals::Theme::text;
ColorPair EngineGlobals::Theme::hilite_text;
ColorPair EngineGlobals::Theme::textbox;
EngineGlobals::Board::Style EngineGlobals::Board::style;
int EngineGlobals::Board::XIcon;
int EngineGlobals::Board::OIcon;

std::string EngineGlobals::Game::currentGame;
std::string EngineGlobals::Game::namePlayer1;
std::string EngineGlobals::Game::namePlayer2;
bool EngineGlobals::Game::turnOnSound;

void EngineGlobals::init()
{
	EngineGlobals::Theme::text        = Colors::pair("white", "default", true);
	EngineGlobals::Theme::hilite_text = Colors::pair("cyan", "default", true);
	EngineGlobals::Theme::textbox     = Colors::pair("default", "cyan");
	EngineGlobals::Board::style = EngineGlobals::Board::NORMAL;
	EngineGlobals::Game::turnOnSound = true;
	EngineGlobals::Board::XIcon = 88;
	EngineGlobals::Board::OIcon = 79;
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

void EngineGlobals::Game::setNamePlayer(std::string name, bool isPlayer1)
{
	if (isPlayer1) EngineGlobals::Game::namePlayer1 = name;
	else EngineGlobals::Game::namePlayer2 = name;
}

void EngineGlobals::Game::setSound()
{
	EngineGlobals::Game::turnOnSound = !EngineGlobals::Game::turnOnSound;
}
