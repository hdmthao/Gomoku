#include <EngineGlobals.hpp>

ColorPair EngineGlobals::Theme::text;
ColorPair EngineGlobals::Theme::hilite_text;
ColorPair EngineGlobals::Theme::textbox;
EngineGlobals::Board::Style EngineGlobals::Board::style;
std::string EngineGlobals::Game::currentGame;
std::string EngineGlobals::Game::namePlayer1;
std::string EngineGlobals::Game::namePlayer2;
void EngineGlobals::init()
{
	EngineGlobals::Theme::text        = Colors::pair("white", "default", true);
	EngineGlobals::Theme::hilite_text = Colors::pair("cyan", "default", true);
	EngineGlobals::Theme::textbox     = Colors::pair("default", "cyan");
	EngineGlobals::Board::style = EngineGlobals::Board::NORMAL;
}

void EngineGlobals::Board::setGameStyle(EngineGlobals::Board::Style _style)
{
	EngineGlobals::Board::style = _style;
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
