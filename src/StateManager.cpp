#include <StateManager.hpp>
#include <Input.hpp>
#include <unistd.h>

StateManager::StateManager():
	currentState(NULL)
{ }

StateManager::~StateManager() {
	if (this->currentState)
		this->currentState->unload();

	if (this->currentState) {
		delete(this->currentState);
		this->currentState = NULL;
	}
}

void StateManager::change(GameState* newState) {
	// "ném" một exception thông báo chuyển trạng thái game
	throw ChangeException(newState);
}
void StateManager::quit() {
	// "ném" một exception thông báo việc thoát game
	throw QuitException();
}
