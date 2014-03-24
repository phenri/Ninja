#include <cmath>
#include <fstream>
#include "util.h"

namespace util {

/* class Timer */

int Timer::time() const
{
	assert(p_running);
	return std::chrono::duration_cast<std::chrono::milliseconds>(now() - p_start).count();
}

Timer::Timer()
{
	reset();
}

void Timer::reset()
{
	p_elapsed = 0;
	p_running = false;
}

void Timer::start()
{
	p_start = now();
	p_running = true;
}

void Timer::stop()
{
	p_elapsed += time();
	p_running = false;
}

int Timer::elapsed() const
{
	int time = p_elapsed;
	if (p_running) time += this->time();
	return time;
}

/* class Lockable */

void Lockable::lock() const
{
	p_mutex.lock();
}

void Lockable::unlock() const
{
	p_mutex.unlock();
}

/* class Waitable */

void Waitable::wait()
{
	p_cond.wait(p_mutex);
}

void Waitable::signal()
{
	p_cond.notify_one();
}

/* helper functions */

int round(double x)
{
	return int(std::floor(x + 0.5));
}

double rand_float()
{
	return double(std::rand()) / (double(RAND_MAX) + 1.0);
}

int rand_int(int n)
{
	assert(n > 0);
	return int(rand_float() * double(n));
}

bool to_bool(const std::string & s)
{
	return s == "true" ? true : false;
}

void log(const std::string & s)
{
	std::ofstream log_file("log.txt", std::ios_base::app);
	log_file << s << std::endl;
}

}	// namespace util

