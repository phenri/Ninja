#include <cassert>
#include "types.h"

int side::opposite(int sd)
{
	return sd ^ 1;
}

namespace square {

int make(int fl, int rk)
{
	assert(fl < 8 && rk < 8);
	return (fl << 3) | rk;
}

int make(int fl, int rk, int sd)
{
	assert(fl < 8 && rk < 8);
	return make(fl, (rk ^ -sd) & 7);
}

int file(int sq)
{
	return sq >> 3;
}

int rank(int sq)
{
	return sq & 7;
}

int rank(int sq, int sd)
{
	return (sq ^ -sd) & 7;
}

int opposit_file(int sq)
{
	return sq ^ 070;
}

int opposit_rank(int sq)
{
	return sq ^ 007;
}

bool is_promotion(int sq)
{
	int rk = rank(sq);
	return rk == RANK_1 || rk == RANK_8;
}

int color(int sq)
{
	return ((sq >> 3) ^ sq) & 1;
}

bool same_color(int s0, int s1)
{
	int diff = s0 ^ s1;
	return (((diff >> 3) ^ diff) & 1) == 0;
}

bool same_line(int s0, int s1)
{
	return file(s0) == file(s1) || rank(s0) == rank(s1);
}

int file_distance(int s0, int s1)
{
	return std::abs(file(s1) - file(s0));
}

int rank_distance(int s0, int s1)
{
	return std::abs(rank(s1) - rank(s0));
}

int distance(int s0, int s1)
{
	return std::max(file_distance(s0, s1), rank_distance(s0, s1));
}

int pawn_inc(int sd)
{
	return (sd == side::WHITE) ? +1 : -1;
}

int stop(int sq, int sd)
{
	return sq + pawn_inc(sd);
}

int promotion(int sq, int sd)
{
	return make(file(sq), RANK_8, sd);
}

bool is_valid_88(int s88)
{
	return (s88 & ~0x77) == 0;
}

int to_88(int sq)
{
	return sq + (sq & 070);
}

int from_88(int s88)
{
	assert(is_valid_88(s88));
	return (s88 + (s88 & 7)) >> 1;
}

int from_fen(int sq)
{
	return make(sq & 7, (sq >> 3) ^ 7);
}

int from_string(const std::string & s)
{
	assert(s.length() == 2);
	return make(s[0] - 'a', s[1] - '1');
}

std::string to_string(int sq)
{
	std::string s;
	s += 'a' + file(sq);
	s += '1' + rank(sq);
	return s;
}

}	// namespace square

const int wing::shelter_file[SIZE] = { square::FILE_G, square::FILE_B };

namespace piece {

bool is_minor(int pc)
{
	assert(pc < SIZE);
	return pc == KNIGHT || pc == BISHOP;
}

bool is_major(int pc)
{
	assert(pc < SIZE);
	return pc == ROOK || pc == QUEEN;
}

bool is_slider(int pc)
{
	assert(pc < SIZE);
	return pc >= BISHOP && pc <= QUEEN;
}

int score(int pc)   // for MVV/LVA
{
	assert(pc < SIZE);
	assert(pc != NONE);
	return pc;
}

int value(int pc)
{
	assert(pc < SIZE);
	static const int value[SIZE] = {PAWN_VALUE, KNIGHT_VALUE, BISHOP_VALUE, ROOK_VALUE, QUEEN_VALUE, KING_VALUE, 0};
	return value[pc];
}

int make(int pc, int sd)
{
	assert(pc < SIZE);
	assert(pc != NONE);
	assert(sd < side::SIZE);
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
	assert(pc < SIZE);
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

