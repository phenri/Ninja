/*
 * Ninja, a UCI chess engine derived from Senpai 1.0
 * Copyright (C) 2014 Fabien Letouzey (Senpai author)
 * Copyright (C) 2014 Lucas Braesch
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
	return p_running ? p_elapsed + time() : p_elapsed;
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

/* class PRNG */

uint64_t PRNG::rol(uint64_t x, uint64_t k) const
{
	return (x << k) | (x >> (64 - k));
}

uint64_t PRNG::rand()
{
	const uint64_t e = a - rol(b,  7);
	a = b ^ rol(c, 13);
	b = c + rol(d, 37);
	c = d + e;
	return d = e + a;
}

void PRNG::init(uint64_t seed)
{
	a = 0xf1ea5eed, b = c = d = seed;
	for (int i = 0; i < 20; ++i)
		rand();
}

PRNG::PRNG()
{
	init();
}

/* helper functions */

int round(double x)
{
	return int(std::floor(x + 0.5));
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

