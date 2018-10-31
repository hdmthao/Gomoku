#include <Input.hpp>

#include <ncurses.h>
#include <sys/select.h>
#include <unistd.h>

int Input::pressedKey = ERR;
std::map<std::string, int> Input::binds;

void Input::update(int delay_ms) {
	Input::pressedKey = Input::getInput(delay_ms);
}

bool Input::noKeyPressed() {
	return (Input::pressedKey == ERR);
}

bool Input::isPressed(int key) {
	return (Input::pressedKey == key);
}

bool Input::isPressed(std::string key) {
	if (Input::binds.find(key) == Input::binds.end())
		return false;

	return (Input::isPressed(Input::binds[key]));
}

char Input::getAlphabet() {
	for (int i = 65; i <= 90; ++i)
	{
		if (Input::isPressed(i)) return (char)(i);
	}
	for (int i = 97; i <= 122; ++i)
	{
		if (Input::isPressed(i)) return (char)(i);
	}
	for (int i = 48; i <= 57; ++i)
	{
		if (Input::isPressed(i)) return (char)(i);
	}
	if (Input::isPressed(95)) return (char)(95);
	return ' ';
}
int Input::getInput(int delay_ms) {
	int retval = 0;
	int c      = 0;

	fd_set input;
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = delay_ms * 1000; // microseconds

	struct timeval* timeout_p = NULL;
	if (delay_ms != -1)
		timeout_p = &timeout;

	FD_ZERO(&input);
	FD_SET(STDIN_FILENO, &input);

	retval = select(FD_SETSIZE, &input, NULL, NULL, timeout_p);

	c = getch();

	if ((retval == 1) && (c == ERR)) // ERROR
		return -1;

	if (retval == 0)
		return ERR;

	return c;
}
