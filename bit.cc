#include <cassert>
#include "bit.h"
#include "types.h"

namespace bit {

bit_t p_left[8];
bit_t p_right[8];
bit_t p_front[8];
bit_t p_rear[8];

bit_t p_side_front[side::SIZE][8];
bit_t p_side_rear[side::SIZE][8];

bit_t bit(int n)
{
	assert(square::ok(n));
	return 1ULL << n;
}

void set(bit_t & b, int n)
{
	b |= bit(n);
}

void clear(bit_t & b, int n)
{
	b &= ~bit(n);
}

bool is_set(bit_t b, int n)
{
	return (b & bit(n)) != 0;
}

void safe_set_bit(bit_t& b, int fl, int rk)
{
	if (square::file_ok(fl) && square::rank_ok(rk))
		set(b, square::make(fl, rk));
}

int first(bit_t b)
{
	assert(b != 0);
	return __builtin_ctzll(b); // GCC
}

bit_t rest(bit_t b)
{
	assert(b != 0);
	return b & (b - 1);
}

int count(bit_t b)
{
	return __builtin_popcountll(b); // GCC
}

bool single(bit_t b)
{
	assert(b != 0);
	return rest(b) == 0;
}

bit_t file(int fl)
{
	assert(square::file_ok(fl));
	return 0xFFULL << (fl * 8);
}

bit_t rank(int rk)
{
	assert(square::rank_ok(rk));
	return 0x0101010101010101ULL << rk;
}

bit_t files(int fl)
{
	assert(square::file_ok(fl));
	bit_t file = bit::file(fl);
	return (file << 8) | file | (file >> 8);
}

bit_t left(int fl)
{
	assert(square::file_ok(fl));
	return p_left[fl];
}

bit_t right(int fl)
{
	assert(square::file_ok(fl));
	return p_right[fl];
}

bit_t front(int rk)
{
	assert(square::rank_ok(rk));
	return p_front[rk];
}

bit_t rear(int rk)
{
	assert(square::rank_ok(rk));
	return p_rear[rk];
}

bit_t front(int sq, int sd)
{
	assert(square::ok(sq) && side::ok(sd));
	return p_side_front[sd][square::rank(sq)];
}

bit_t rear(int sq, int sd)
{
	assert(square::ok(sq) && side::ok(sd));
	return p_side_rear[sd][square::rank(sq)];
}

void init()
{
	{
		bit_t bf = 0;
		bit_t br = 0;

		for (int i = 0; i < 8; i++) {
			p_left[i] = bf;
			p_rear[i] = br;
			bf |= file(i);
			br |= rank(i);
		}
	}

	{
		bit_t bf = 0;
		bit_t br = 0;

		for (int i = 7; i >= 0; i--) {
			p_right[i] = bf;
			p_front[i] = br;
			bf |= file(i);
			br |= rank(i);
		}
	}

	for (int rk = 0; rk < 8; rk++) {
		p_side_front[side::WHITE][rk] = front(rk);
		p_side_front[side::BLACK][rk] = rear(rk);
		p_side_rear [side::WHITE][rk] = rear(rk);
		p_side_rear [side::BLACK][rk] = front(rk);
	}
}

}	// namespace bit

