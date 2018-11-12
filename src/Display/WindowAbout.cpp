#include <Display/WindowAbout.hpp>
#include <Display/Colors.hpp>
#include <EngineGlobals.hpp>
#include <Input.hpp>
#include <Helpers/Utils.hpp>

WindowAbout::WindowAbout(int screenWidth, int screenHeight) {
	int width  = 60;
	int height = 18;

	int windowx = screenWidth/2 - 4;
	int windowy = screenHeight/2 - 1;

	this->main = new Window(windowx, windowy, width, height);

	// Help
	this->intro = new Window(this->main, 0, 0, 0, 0);
	this->intro->borders(Window::BORDER_NONE);

	this->credit = new Window(this->main, 0, 0, 0, 0);
	this->credit->borders(Window::BORDER_NONE);

	this->helpWin = new Window(127, 20, 24, 5);

}
WindowAbout::~WindowAbout()
{
	SAFE_DELETE(this->main);
	SAFE_DELETE(this->intro);
	SAFE_DELETE(this->credit);
	SAFE_DELETE(this->helpWin);
}
void WindowAbout::run() {
	int activatedIndex = 0;

	while (true)
	{
		// Tải trang
		this->main->clear();
		if (activatedIndex == 0) this->intro->clear(); else this->credit->clear();

		this->helpWin->setTitle("Help");
		this->helpWin->borders(Window::BORDER_FANCY);
		this->helpWin->clear();

		this->main->print(((activatedIndex == 0) ?
		                   "[Intro]" :
		                   " Intro "),
		                  20,
		                  0,
		                  ((activatedIndex == 0) ?
		                   Colors::pair("yellow", "default", true) :
		                   Colors::pair("red", "default", true)));

		this->main->print(((activatedIndex == 1) ?
		                   "[Credits]" :
		                   " Credits "),
		                  28,
		                  0,
		                  ((activatedIndex == 1) ?
						   Colors::pair("yellow", "default", true) :
		                   Colors::pair("red", "default", true)));

		if (activatedIndex == 0) {
			this->helpWin->print("Credits", 2, 2, Colors::pair("cyan", "default", true));
			this->helpWin->print("Key-Right", 14, 2);
			this->helpWin->print("Back", 2, 3, Colors::pair("cyan", "default", true));
			this->helpWin->print("Esc", 14, 3);

			this->intro->print("\n",
			                        0, 0);
			this->intro->print(Utils::String::split("Are you looking for a AWESOME game???\n"
													"\n"
			                                        "You think you are SMART engouh???\n"
													"\n"
													"Do you want to have a NICE time with friends???\n"
													"\n"
			                                        "            WONDERFUL!!!!\n"
													"\n"
			                                        "Wellcome to GOMOKU game - an abstract strategy board game\n"
													"\n"
			                                             "Let play it, discover the mystery, and become the WINNER! \n"
			                                             "", '\n'),
			                        1, 1, Colors::pair("white", "default", true));
			this->intro->print(Utils::String::split("More about GOMOKU:\n"
													" https://en.wikipedia.org/wiki/Gomoku"
													, '\n'),
													1, 13, Colors::pair("white", "default"));
		}
		//
		// Credits
		else if (activatedIndex == 1)
		{
			this->helpWin->print("Introdution", 2, 2, Colors::pair("cyan", "default", true));
			this->helpWin->print("Key-Left", 14, 2);
			this->helpWin->print("Back", 2, 3, Colors::pair("cyan", "default", true));
			this->helpWin->print("Esc", 14, 3);

			this->credit->print(Utils::String::split(" _______   _____    _     _    _____   _    _  _      _\n"
											   		  "|  _ _  | / ___ \\  / \\   / \\  /     \\ | |  / || |    | |\n"
											   		  "|_| /_| || |___| ||  _\\_/_  ||  ___  ||_|_/_/ | |    | |\n"
											   		  "   /__| ||       || |     | || |___| ||_|_|_  | |____| |\n"
											   		  "  |_____| \\_____/ |_|     |_| \\_____/ |_| \\_\\ |__\\__/__|", '\n'),
										   0, 0, Colors::pair("yellow", "default", true));

			this->credit->print(" version 1.0.0                (built  01-10-2018)",
			                        0, 5,
			                        Colors::pair("green", "default", true));

			this->credit->print(Utils::String::split(
			                                             "\n"
			                                             "This is a project game made by HiMT :D,\n"
			                                             "contact us at <mthaohd.itk4@gmail.com>\n"
			                                             "Thank you for playing this game :)\n"
			                                             "\n"
			                                             "Source Code:\n"
			                                             " https://github.com/himt-097/gomoku/", '\n'),
			                        0, 6, Colors::pair("white", "default", true));
		}

		if (activatedIndex == 0) this->intro->refresh(); else this->credit->refresh();

		this->helpWin->refresh();
		this->main->refresh();

		refresh();

		// xử lí input từ user
		Input::update();

		if (Input::isPressed(KEY_LEFT))
		{
			activatedIndex--;
			if (activatedIndex < 0)
				activatedIndex = 0;
		}
		else if (Input::isPressed(KEY_RIGHT))
		{
			activatedIndex++;
			if (activatedIndex > 1)
				activatedIndex = 1;
		}
		else if (Input::isPressed(27))
		{
			this->helpWin->borders(Window::BORDER_NONE);
			this->helpWin->clear();
			this->helpWin->refresh();

			return;
		}
	}
}
