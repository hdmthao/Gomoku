#include <Display/WindowAbout.hpp>
#include <Engine/Graphics/Colors.hpp>
#include <Engine/EngineGlobals.hpp>
#include <Engine/Input.hpp>
#include <Engine/Helpers/Utils.hpp>

WindowAbout::WindowAbout(int screenWidth, int screenHeight) {
	int width  = 60;
	int height = 18;

	int windowx = screenWidth/2 - 10;
	int windowy = screenHeight/2 - 5;

	this->main = new Window(windowx, windowy, width, height);

	// Help
	this->intro = new Window(this->main, 0, 0, WINDOW_FILL, WINDOW_FILL);
	this->intro->borders(Window::BORDER_NONE);

	this->credit = new Window(this->main, 0, 0, WINDOW_FILL, WINDOW_FILL);
	this->credit->borders(Window::BORDER_NONE);
}

void WindowAbout::run() {
	int activatedIndex = 0;

	while (true)
	{
		// Tải trang
		this->main->clear();
		if (activatedIndex == 0) this->intro->clear(); else this->credit->clear();

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
			this->intro->print("\n",
			                        0, 0,
			                        EngineGlobals::Theme::hilite_text);
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
													1, 12, Colors::pair("white", "defualt"));
			this->credit->print(Utils::String::split("Press KeyRight To Open Credits\n"
													 "Press Enter To Return Main Menu\n", '\n'),
													13, 14, Colors::pair("red", "default", true));

		}
		//
		// Credits
		else if (activatedIndex == 1)
		{
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
														 "Thanks <eu@alexdantas.net> for support ^^\n"
			                                             "Thank you for playing this game :)\n"
			                                             "\n"
			                                             "Source Code:\n"
			                                             " https://github.com/himt-097/gomoku/", '\n'),
			                        0, 6, Colors::pair("white", "default", true));
			this->credit->print(Utils::String::split(   "Press KeyLeft To Open Intro\n"
														"Press Enter To Return Main Menu\n"
													 , '\n'),
								13, 14, Colors::pair("red", "default", true));
		}

		if (activatedIndex == 0) this->intro->refresh(); else this->credit->refresh();
		this->main->refresh();
		refresh();

		// xử lí input từ user
		Input::update();

		if (Input::isPressed("left") || // user-defined
		    Input::isPressed(KEY_LEFT))
		{
			activatedIndex--;
			if (activatedIndex < 0)
				activatedIndex = 0;
		}
		else if (Input::isPressed("right") || // user-defined
		         Input::isPressed(KEY_RIGHT))
		{
			activatedIndex++;
			if (activatedIndex > 1)
				activatedIndex = 1;
		}
		else if (Input::isPressed("quit") ||
		         Input::isPressed(KEY_ENTER) ||
		         Input::isPressed('\n'))
			return;
	}
}
