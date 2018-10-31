#include <EngineGlobals.hpp>

ColorPair EngineGlobals::Theme::text;
ColorPair EngineGlobals::Theme::hilite_text;
ColorPair EngineGlobals::Theme::textbox;
EngineGlobals::Board::Style EngineGlobals::Board::style;
std::string EngineGlobals::Game::currentGame;
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
