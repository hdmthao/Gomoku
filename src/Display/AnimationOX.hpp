#ifndef AnimationOX_H_DEFINED
#define AnimationOX_H_DEFINED

#include "Animation.hpp"
#include <Helpers/Timer.hpp>

#include <vector>

#define MAX_SNAKES 100

struct OX
{
	int x;
	int y;
	int size;

	OX(int x, int y, int size):
		x(x),
		y(y),
		size(size)
	{ }
};

/// Rules and behavior of the Fire animation.
class AnimationOX: public Animation
{
public:
	AnimationOX(Window* window);
	virtual ~AnimationOX() {};

	void load();
	void update();
	void draw();

private:
	std::vector<OX> ox;

	/// Timer to update all snakes.
	Timer updateTimer;

	/// Timer to add another snake.
	Timer addTimer;

	void add();
};

#endif //AnimationOX_H_DEFINED
