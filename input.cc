#include <iostream>
#include "input.h"

namespace input {

/* class Input */

Input::Input()
{
	p_has_input = false;
	p_eof = false;
}

bool Input::has_input() const
{
	return p_has_input;
}

bool Input::get_line(std::string & line)
{
	lock();

	while (!p_has_input)
		wait();

	bool line_ok = !p_eof;
	if (line_ok)
		line = p_line;

	p_has_input = false;
	signal();

	unlock();

	return line_ok;
}

void Input::set_eof()
{
	lock();

	while (p_has_input)
		wait();

	p_eof = true;

	p_has_input = true;
	signal();

	unlock();
}

void Input::set_line(std::string & line)
{
	lock();

	while (p_has_input)
		wait();

	p_line = line;

	p_has_input = true;
	signal();

	unlock();
}

/* global objects */

Input input;
std::thread thread;

void input_program(Input *input)
{
	std::string line;

	while (std::getline(std::cin, line))
		input->set_line(line);

	input->set_eof();
}

void init()
{
	thread = std::thread(input_program, &input);
	thread.detach();
}

}	// namespace input

