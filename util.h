#pragma once
#include <cassert>
#include <string>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

namespace util {

class Timer
{
	typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_t;

	int p_elapsed;
	bool p_running;
	time_t p_start;

	static time_t now() { return std::chrono::high_resolution_clock::now(); }
	int time() const;

public:
	Timer();

	void reset();
	void start();
	void stop();
	int elapsed() const;
};

class Lockable
{
protected: // HACK for Waitable::wait()
	mutable std::mutex p_mutex;

public:
	void lock() const;
	void unlock() const;
};

class Waitable : public Lockable
{
	std::condition_variable_any p_cond;

public:
	void wait();
	void signal();
};

extern int round(double x);
extern double rand_float();
extern int rand_int(int n);
extern bool to_bool(const std::string & s);
extern void log(const std::string & s);

}	// namespace util

