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
#pragma once
#include <cassert>
#include <cstdint>
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

class Waitable
{
	mutable std::mutex p_mutex;
	std::condition_variable_any p_cond;

public:
	void lock() const;
	void unlock() const;

	void wait();
	void signal();
};

class PRNG
{
	uint64_t a, b, c, d;	// 256-bit state
	uint64_t rol(uint64_t x, unsigned k) const;

public:
	PRNG();

	void init(uint64_t seed = 0);
	uint64_t rand();
};

extern int round(double x);
extern bool to_bool(const std::string & s);
extern void log(const std::string & s);

}	// namespace util

