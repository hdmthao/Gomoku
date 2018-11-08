#ifndef TIMER_H_DEFINED
#define TIMER_H_DEFINED

#include <sys/time.h>

///
class Timer
{
public:
	Timer();

	/// Sets a starting point for the timer.
	/// If called multiple times, will restart.
	void start();

	bool isRunning();
	/// Returns the whole timer's difference in milisseconds.
	//	@note If the timer's not started, will return 0.
	suseconds_t delta_us();

	/// Returns the milisseconds part of the timer's difference.
	suseconds_t delta_ms();

	/// Returns the seconds part of the timer's difference.
	suseconds_t delta_s();

protected:
	suseconds_t startMark;

	bool running;
};

#endif /* TIMER_H_DEFINED */
