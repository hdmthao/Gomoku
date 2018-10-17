#include <Display/Menu.hpp>
#include <Helpers/Utils.hpp>
#include <EngineGlobals.hpp>
#include <Input.hpp>

Menu::Menu(int x, int y, int width, int height):
	current(NULL),
	currentIndex(0),
	x(x),
	y(y),
	width(width),
	height(height),
	selected(false),
	selectedItem(NULL)
{ }
Menu::~Menu()
{
	for (unsigned int i = 0; i < (this->item.size()); i++)
		SAFE_DELETE(this->item[i]);

	this->item.clear();
}

void Menu::add(MenuItem* item)
{
	this->item.push_back(item);

	if (this->item.size() == 1)
	{
		this->current      = this->item.back();
		this->currentIndex = this->item.size() - 1;
	}

	unsigned int i = 0;
	for (i = 0; i < (this->item.size()); i++)
		if (this->item[i])
			break;

	this->current      = this->item[i];
	this->currentIndex = i;
}

void Menu::draw(Window* window)
{
	for (unsigned int curitem = 0, yoffset = 0; curitem < this->item.size(); curitem++, yoffset++) {
		this->item[curitem]->draw(window, this->x, this->y + yoffset, this->width, (this->item[curitem] == this->current));
	}
}

void Menu::handleInput()
{
	if (Input::noKeyPressed())
		return;

	if (Input::isPressed("down") ||
	    Input::isPressed(KEY_DOWN) ||
	    Input::isPressed('\t'))
		this->goNext();

	else if (Input::isPressed("up") ||
	         Input::isPressed(KEY_UP) ||
	         Input::isPressed(KEY_BTAB))
		this->goPrevious();
	else if (Input::isPressed(KEY_ENTER) ||
	         Input::isPressed('\n'))
	{
		if (this->current->type == MenuItem::ITEM ||
			this->current->type == MenuItem::LABEL)
		{
			this->selected = true;
			this->selectedItem = this->current;
		}
		else
			this->current->handleInput();
	}
	else
	{
		if (this->current)
			this->current->handleInput();
	}
}

void Menu::goNext()
{
	if (this->item.size() == 0)
		return;

	if (this->item.size() == 1)
	{
		this->current = *(this->item.begin());
		this->currentIndex = 0;
		return;
	}

	if (this->current == this->item.back())
	{
		return;
	}

	this->currentIndex++;
	this->current = this->item[this->currentIndex];
}

void Menu::goPrevious()
{
	if (this->item.size() == 0)
		return;

	if (this->item.size() == 1)
	{
		this->current = this->item.front();
		this->currentIndex = 0;
		return;
	}

	if (this->current == this->item.front())
	{
		return;
	}

	this->currentIndex--;
	this->current = this->item[this->currentIndex];
}

bool Menu::willQuit()
{
	// Thoát nếu như user chọn một item
	return (this->selected && this->selectedItem);
}

std::string Menu::currentLabel()
{
	return (this->current->label);
}

int Menu::currentID()
{
	return (this->current->id);
}


void Menu::reset()
{
	this->selected = false;
	this->selectedItem = NULL;
}
