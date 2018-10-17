#include <Engine/EngineGlobals.hpp>

ColorPair EngineGlobals::Theme::text;
ColorPair EngineGlobals::Theme::hilite_text;
ColorPair EngineGlobals::Theme::textbox;


void EngineGlobals::init()
{
	EngineGlobals::Theme::text        = Colors::pair("white", "default", true);
	EngineGlobals::Theme::hilite_text = Colors::pair("cyan", "default", true);
	EngineGlobals::Theme::textbox     = Colors::pair("default", "cyan");
}
