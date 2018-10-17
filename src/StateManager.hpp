#ifndef STATEMANAGER_H_DEFINED
#define STATEMANAGER_H_DEFINED

#include <GameState.hpp>
#include <exception>

class ChangeException : public std::exception {
public:
	ChangeException(GameState* newState):
		newState(newState)
	{ }

	GameState* newState;
};

class QuitException : public std::exception {
public:
	QuitException()
	{ }
};


class StateManager {
public:
	StateManager();
	virtual ~StateManager();

	// chuyển trạng thái của game
	static void change(GameState* newState);

	// thoát game
	static void quit();

	// Trạng thái hiện tại của game
	GameState* currentState;

};

#endif /* STATEMANAGER_H_DEFINED */
