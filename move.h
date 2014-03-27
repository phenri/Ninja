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
#include "types.h"

namespace move {

const int FLAGS_BITS = 9;
const int FLAGS_SIZE = 1 << FLAGS_BITS;
const int FLAGS_MASK = FLAGS_SIZE - 1;

const int BITS = FLAGS_BITS + 12;
const int SIZE = 1 << BITS;
const int MASK = SIZE - 1;

const int SCORE_BITS = 32 - BITS;
const int SCORE_SIZE = 1 << SCORE_BITS;
const int SCORE_MASK = SCORE_SIZE - 1;

enum Move {NONE};

int make_flags(int pc, int cp, int pp = piece::NONE);
int make(int f, int t, int pc, int cp, int pp = piece::NONE);
int from(int mv);
int to(int mv);
int piece(int mv);
int cap(int mv);
int prom(int mv);
int flags(int mv);
std::string to_can(int mv);

}	// namespace move

