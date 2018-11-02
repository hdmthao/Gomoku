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
	deleted(false),
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
void Menu::addBlank()
{
	this->item.push_back(NULL);
}
void Menu::draw(Window* window)
{
	unsigned int draw_begin = 0;
	unsigned int draw_end   = this->item.size();

	if (this->height < (int)this->item.size())
	{
		if ((int)this->currentIndex <= this->height/2)
		{
			draw_end = this->height - 1;
		}
		else if ((int)this->currentIndex < ((int)this->item.size() - this->height/2) - 1)
		{
			draw_begin = this->currentIndex - this->height/2;
			draw_end   = this->currentIndex + this->height/2;
		}
		else
		{
			draw_begin = this->item.size() - this->height;
		}
	}

	for (unsigned int curitem = draw_begin, yoffset = 0; curitem < draw_end; curitem++, yoffset++)
	{
		if ((curitem == draw_begin) && (curitem != 0))
		{
			window->print("(more)", this->x + this->width/2 - 3, this->y + yoffset, Colors::pair("white", "default"));
			continue;
		}
		if ((curitem == draw_end - 1) && (curitem != this->item.size() - 1))
		{
			window->print("(more)", this->x + this->width/2 - 3, this->y + yoffset + 1, Colors::pair("white", "default"));
			continue;
		}
		if (! this->item[curitem])
		{
			for (int j = 0; j < (this->width); j++)
				window->printChar(
								   ACS_HLINE,
								  this->x + j,
								  this->y + yoffset,
								  Colors::pair("white", "default"));
		} else
		this->item[curitem]->draw(window, this->x, this->y + yoffset, this->width, (this->item[curitem] == this->current));
	}
}

void Menu::handleInput()
{
	if (Input::noKeyPressed())
		return;

	if (Input::isPressed(KEY_DOWN)) this->goNext();
	else if (Input::isPressed(KEY_UP)) this->goPrevious();
	else if (Input::isPressed('\n'))
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
	else if (Input::isPressed(97))
	{
		if (this->current->type == MenuItem::ITEM || this->current->type == MenuItem::LABEL)
		{
			this->deleted = true;
			this->selectedItem = this->current;
		}
		else this->current->handleInput();
	}
	else
	{
		if (this->current) this->current->handleInput();
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

	if (!this->current) this->goNext();
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

	if (!this->current) this->goPrevious();
}

bool Menu::willQuit()
{
	// Thoát nếu như user chọn một item
	return (this->selected && this->selectedItem);
}

bool Menu::willDelete()
{
	return (this->deleted && this->selectedItem);
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
