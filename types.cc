#include <cassert>
#include "types.h"

namespace side {

bool ok(int sd)
{
	return 0 <= sd && sd < SIZE;
}

int opposite(int sd)
{
	assert(ok(sd));
	return sd ^ 1;
}

}	// namespace side

namespace square {

bool ok(int sq)
{
	return 0 <= sq && sq < SIZE;
}

bool file_ok(int fl)
{
	return 0 <= fl && fl < FILE_SIZE;
}

bool rank_ok(int rk)
{
	return 0 <= rk && rk < RANK_SIZE;
}

int make(int fl, int rk)
{
	assert(file_ok(fl) && rank_ok(rk));
	return (fl << 3) | rk;
}

int make(int fl, int rk, int sd)
{
	assert(file_ok(fl) && rank_ok(rk));
	assert(side::ok(sd));
	return make(fl, (rk ^ -sd) & 7);
}

int file(int sq)
{
	assert(ok(sq));
	return sq >> 3;
}

int rank(int sq)
{
	assert(ok(sq));
	return sq & 7;
}

int rank(int sq, int sd)
{
	assert(ok(sq));
	return (sq ^ -sd) & 7;
}

int opposit_file(int sq)
{
	assert(ok(sq));
	return sq ^ 070;
}

int opposit_rank(int sq)
{
	assert(ok(sq));
	return sq ^ 007;
}

bool is_promotion(int sq)
{
	assert(ok(sq));
	int rk = rank(sq);
	return rk == RANK_1 || rk == RANK_8;
}

int color(int sq)
{
	assert(ok(sq));
	return ((sq >> 3) ^ sq) & 1;
}

bool same_color(int s0, int s1)
{
	assert(ok(s0) && ok(s1));
	int diff = s0 ^ s1;
	return (((diff >> 3) ^ diff) & 1) == 0;
}

bool same_line(int s0, int s1)
{
	assert(ok(s0) && ok(s1));
	return file(s0) == file(s1) || rank(s0) == rank(s1);
}

int file_distance(int s0, int s1)
{
	assert(ok(s0) && ok(s1));
	return std::abs(file(s1) - file(s0));
}

int rank_distance(int s0, int s1)
{
	assert(ok(s0) && ok(s1));
	return std::abs(rank(s1) - rank(s0));
}

int distance(int s0, int s1)
{
	assert(ok(s0) && ok(s1));
	return std::max(file_distance(s0, s1), rank_distance(s0, s1));
}

int pawn_inc(int sd)
{
	assert(side::ok(sd));
	return (sd == side::WHITE) ? +1 : -1;
}

int stop(int sq, int sd)
{
	assert(ok(sq) && side::ok(sd));
	return sq + pawn_inc(sd);
}

int promotion(int sq, int sd)
{
	assert(ok(sq) && side::ok(sd));
	return make(file(sq), RANK_8, sd);
}

bool is_valid_88(int s88)
{
	return (s88 & ~0x77) == 0;
}

int to_88(int sq)
{
	assert(ok(sq));
	return sq + (sq & 070);
}

int from_88(int s88)
{
	assert(is_valid_88(s88));
	return (s88 + (s88 & 7)) >> 1;
}

int from_fen(int sq)
{
	assert(ok(sq));
	return make(sq & 7, (sq >> 3) ^ 7);
}

int from_string(const std::string & s)
{
	assert(s.length() == 2);
	return make(s[0] - 'a', s[1] - '1');
}

std::string to_string(int sq)
{
	assert(ok(sq));

	std::string s;
	s += 'a' + file(sq);
	s += '1' + rank(sq);

	return s;
}

}	// namespace square

const int wing::shelter_file[SIZE] = { square::FILE_G, square::FILE_B };

namespace piece {

const std::string Char = "PNBRQK?";
const std::string Fen_Char = "PpNnBbRrQqKk";

bool ok(int pc)
{
	return 0 <= pc && pc < SIZE;
}

bool is_minor(int pc)
{
	assert(ok(pc));
	return pc == KNIGHT || pc == BISHOP;
}

bool is_major(int pc)
{
	assert(ok(pc));
	return pc == ROOK || pc == QUEEN;
}

bool is_slider(int pc)
{
	assert(ok(pc));
	return pc >= BISHOP && pc <= QUEEN;
}

int score(int pc)   // for MVV/LVA
{
	assert(ok(pc));
	assert(pc != NONE);
	return pc;
}

int value(int pc)
{
	assert(ok(pc));
	static const int value[SIZE] = {PAWN_VALUE, KNIGHT_VALUE, BISHOP_VALUE, ROOK_VALUE, QUEEN_VALUE, KING_VALUE, 0};
	return value[pc];
}

int make(int pc, int sd)
{
	assert(ok(pc));
	assert(pc != NONE);
	assert(side::ok(sd));
	return (pc << 1) | sd;
}

int piece(int p12)
{
	assert(p12 < SIDE_SIZE);
	return p12 >> 1;
}

int side(int p12)
{
	assert(p12 < SIDE_SIZE);
	return p12 & 1;
}

int from_char(char c)
{
	return Char.find(c);
}

char to_char(int pc)
{
	assert(ok(pc));
	return Char[pc];
}

int from_fen(char c)
{
	return Fen_Char.find(c);
}

char to_fen(int p12)
{
	assert(p12 < SIDE_SIZE);
	return Fen_Char[p12];
}

}	// namespace piece

