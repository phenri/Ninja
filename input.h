#pragma once
#include "util.h"

namespace input {

class Input : public util::Waitable
{
	bool volatile p_has_input;
	bool p_eof;
	std::string p_line;

public:
	Input();

	bool has_input() const;
	bool get_line(std::string & line);
	void set_eof();
	void set_line(std::string & line);
};

extern Input input;
extern std::thread thread;

extern void input_program(Input *input);
extern void init();

}	// namespace input

