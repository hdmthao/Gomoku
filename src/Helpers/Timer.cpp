#include <Helpers/Timer.hpp>

#include <iostream>				// NULL

// How many microseconds exists in a second
#define MICRO_IN_SECONDS 1000000

// Local functino that returns current microsecond
// amount since the Epoch.
//
static suseconds_t get_ticks()
{
	struct timeval tmp;
	gettimeofday(&(tmp), NULL);

	return tmp.tv_usec + (tmp.tv_sec * MICRO_IN_SECONDS);
}

Timer::Timer():
	startMark(0),
	running(false)
{}
void Timer::start()
{
    this->startMark  = get_ticks();
    this->running    = true;
}
bool Timer::isRunning()
{
    return this->running;
}
suseconds_t Timer::delta_us()
{
    if (this->isRunning())
	    return get_ticks() - this->startMark;
}
suseconds_t Timer::delta_ms()
{
    return this->delta_us() / 1000;
}
suseconds_t Timer::delta_s()
{
    return this->delta_ms() / 1000;
}
