#include <Engine/Graphics/Layout.hpp>
#include <Engine/Helpers/Utils.hpp>

#include <cstdlib>


int Width;
int Height;

Layout::Layout(int width, int height):
	main(NULL)
{
	Width  = width;
	Height = height;
}
Layout::~Layout()
{ }
void Layout::windowsInit()
{
	clear();

	int current_height, current_width;
	getmaxyx(stdscr, current_height, current_width);

	int main_x = 0;
	int main_y = 0;

	main_x = current_width/2 - Width/2;

	main_y = current_height/2 - Height/2;

	this->main = new Window(main_x, main_y, Width, Height);

	this->main->refresh();
}
void Layout::windowsExit()
{
	SAFE_DELETE(this->main);
}
void Layout::draw()
{
}
