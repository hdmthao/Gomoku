#include <Display/AnimationOX.hpp>
#include <Engine/Graphics/Colors.hpp>
#include <Engine/Helpers/Utils.hpp>
#include <stdlib.h>

AnimationOX::AnimationOX(Window* window):
	Animation(window)
{ }
void AnimationOX::load() {
	this->add();

	updateTimer.start();
	addTimer.start();
}
void AnimationOX::update()
{
	// Adding yet another snake
	int delay = (rand() % 3 + 1) * 100;

	if ((addTimer.delta_ms() > delay) &&
	    (this->ox.size() < MAX_SNAKES))
	{
		this->add();

		// Random add burst!
		int x = rand() % 100;
		x = (x < 25);
		if (x)
		{
			int size = rand() % 3 + 3;
			for (int i = 0; i < size; i++)
				this->add();
		}

		addTimer.start();
	}

	// Updating all snakes
	// They all drop once and get deleted as soon as they
	// leave the Window.
	if (updateTimer.delta_ms() > 50)
	{
		std::vector<OX>::iterator it = this->ox.begin();

		while (it != this->ox.end())
		{
			if (((*it).y - (*it).size) > (this->window->getH() - 1))
			{
				it = this->ox.erase(it);
			}
			else
			{
				(*it).y++;
				++it;
			}
		}
		updateTimer.start();
	}
}
void AnimationOX::draw()
{
	for (unsigned int i = 0; i < (this->ox.size()); i++)
	{
		window->printChar('x',
		                  this->ox[i].x,
		                  this->ox[i].y,
		                  Colors::pair("cyan", "default", true));

		for (int j = 1; j < (this->ox[i].size); j++)
		{
			if (j % 2 != 0) {
				window->printChar('x',
			                  	this->ox[i].x,
			                  	this->ox[i].y - j,
			                  	Colors::pair("cyan", "default"));
			} else {
				window->printChar('o',
			                  	this->ox[i].x,
			                  	this->ox[i].y - j,
			                  	Colors::pair("cyan", "default"));
			}
		}
	}
}

void AnimationOX::add()
{
	int newx = rand() % (this->window->getW() - 1) + 1;
	int newy = rand() % 4;
	int size = rand() % 13 + 2;

	this->ox.push_back(OX(newx, newy, size));
}
