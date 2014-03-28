#pragma once
#include <cstdint>
#include "types.h"

typedef uint64_t bit_t;

namespace bit {

extern bit_t p_left[8];
extern bit_t p_right[8];
extern bit_t p_front[8];
extern bit_t p_rear[8];

extern bit_t p_side_front[side::SIZE][8];
extern bit_t p_side_rear[side::SIZE][8];

extern bit_t bit(int n);
extern void set(bit_t & b, int n);
extern void clear(bit_t & b, int n);
extern bool is_set(bit_t b, int n);
extern void safe_set_bit(bit_t& b, int fl, int rk);
extern int first(bit_t b);
extern bit_t rest(bit_t b);
extern int count(bit_t b);
extern bool single(bit_t b);
extern bit_t file(int fl);
extern bit_t rank(int rk);
extern bit_t files(int fl);
extern bit_t left(int fl);
extern bit_t right(int fl);
extern bit_t front(int rk);
extern bit_t rear(int rk);
extern bit_t front(int sq, int sd);
extern bit_t rear(int sq, int sd);

void init();

}	// namespace bit

