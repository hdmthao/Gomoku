#ifndef Input_H_DEFINED
#define Input_H_DEFINED

#include <string>
#include <map>

namespace Input
{

	bool noKeyPressed();

	bool isPressed(int key);


	int getInput(int delay_ms=-1);
	// Nếu delay_ms = -1 thì sẽ đợi cho đến khi user bấm phím
	// Nếu delay_ms = 0 thì sẽ return dù user có bấm hay không
	// Nếu delay_ms > 0 thì sẽ đợi user bấm phím trong delay_ms milisecond.
	void update(int delay_ms=0);

	char getAlphabet();
	char getIcon();

	// phím nào đã được nhấn
	extern int pressedKey;

};

#endif //Input_H_DEFINED
