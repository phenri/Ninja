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
#include <cassert>
#include "move.h"

namespace move {

int make_flags(int pc, int cp, int pp)
{
	assert(piece::ok(pc));
	assert(piece::ok(cp));
	assert(piece::ok(pp));

	return (pc << 6) | (cp << 3) | pp;
}

int make(int f, int t, int pc, int cp, int pp)
{
	assert(square::ok(f));
	assert(square::ok(t));
	assert(piece::ok(pc));
	assert(piece::ok(cp));
	assert(piece::ok(pp));

	assert(pc != piece::NONE);
	assert(pp == piece::NONE || pc == piece::PAWN);

	return (pc << 18) | (cp << 15) | (pp << 12) | (f << 6) | t;
}

int from(int mv)
{
	assert(mv != NONE);
	return (mv >> 6) & 077;
}

int to(int mv)
{
	assert(mv != NONE);
	return mv & 077;
}

int piece(int mv)
{
	assert(mv != NONE);
	return (mv >> 18) & 7;
}

int cap(int mv)
{
	assert(mv != NONE);
	return (mv >> 15) & 7;
}

int prom(int mv)
{
	assert(mv != NONE);
	return (mv >> 12) & 7;
}

int flags(int mv)
{
	assert(mv != NONE);
	return (mv >> 12) & 0777;
}

std::string to_can(int mv)
{
	assert(mv != NONE);

	std::string s;
	s += square::to_string(from(mv));
	s += square::to_string(to(mv));

	if (prom(mv) != piece::NONE)
		s += std::tolower(piece::to_char(prom(mv)));

	return s;
}

}	// namespace move

