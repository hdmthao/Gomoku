#include <Display/MenuItem.hpp>
#include <EngineGlobals.hpp>
#include <Helpers/Utils.hpp>
#include <Input.hpp>

MenuItem::MenuItem(std::string label, int id):
	type(MenuItem::ITEM),
	label(label),
	id(id)
{ }

void MenuItem::draw(Window* window, int x, int y, int width, bool isCurrentItem)
{
	if (isCurrentItem)
	{
		window->print(">> ", x, y, Colors::pair("red", "default", true));
		window->print(this->label.substr(0, width), x + 3, y, Colors::pair("cyan", "default", true));
	} else
	window->print(this->label.substr(0, width), x + 2, y, Colors::pair("white", "default"));
}

void MenuItem::handleInput() { }
