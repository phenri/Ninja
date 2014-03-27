#pragma once
#include <string>

namespace side {

enum {WHITE, BLACK, SIZE};

extern bool ok(int sd);
extern int opposite(int sd);

}

namespace square {

enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_SIZE};
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_SIZE};

enum {
	NONE = -1,
	A1, A2, A3, A4, A5, A6, A7, A8,
	B1, B2, B3, B4, B5, B6, B7, B8,
	C1, C2, C3, C4, C5, C6, C7, C8,
	D1, D2, D3, D4, D5, D6, D7, D8,
	E1, E2, E3, E4, E5, E6, E7, E8,
	F1, F2, F3, F4, F5, F6, F7, F8,
	G1, G2, G3, G4, G5, G6, G7, G8,
	H1, H2, H3, H4, H5, H6, H7, H8,
	SIZE
};

enum {
	INC_LEFT  = -8,
	INC_RIGHT = +8,
	CASTLING_DELTA = 16,
	DOUBLE_PAWN_DELTA = 2,
};

extern bool ok(int sq);

extern int make(int fl, int rk);
extern int make(int fl, int rk, int sd);
extern int file(int sq);
extern int rank(int sq);
extern int rank(int sq, int sd);
extern int opposit_file(int sq);
extern int opposit_rank(int sq);
extern bool is_promotion(int sq);
extern int color(int sq);
extern bool same_color(int s0, int s1);
extern bool same_line(int s0, int s1);
extern int file_distance(int s0, int s1);
extern int rank_distance(int s0, int s1);
extern int distance(int s0, int s1);
extern int pawn_inc(int sd);
extern int stop(int sq, int sd);
extern int promotion(int sq, int sd);

extern bool is_valid_88(int s88);
extern int to_88(int sq);
extern int from_88(int s88);

extern int from_fen(int sq);
extern int from_string(const std::string & s);
extern std::string to_string(int sq);

}	// namespace square

namespace wing {

enum {KING, QUEEN, SIZE};

extern const int shelter_file[SIZE];

}

namespace piece {

enum Piece {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE, SIZE};

enum Side_Piece {
	WHITE_PAWN, BLACK_PAWN,
	WHITE_KNIGHT, BLACK_KNIGHT,
	WHITE_BISHOP, BLACK_BISHOP,
	WHITE_ROOK, BLACK_ROOK,
	WHITE_QUEEN, BLACK_QUEEN,
	WHITE_KING, BLACK_KING,
	SIDE_SIZE
};

static const int PAWN_VALUE   = 100;
static const int KNIGHT_VALUE = 325;
static const int BISHOP_VALUE = 325;
static const int ROOK_VALUE   = 500;
static const int QUEEN_VALUE  = 975;
static const int KING_VALUE   = 10000; // for SEE

static const std::string Char = "PNBRQK?";
static const std::string Fen_Char = "PpNnBbRrQqKk";

extern bool ok(int pc);

extern bool is_minor(int pc);
extern bool is_major(int pc);
extern bool is_slider(int pc);
extern int score(int pc);
extern int value(int pc);
extern int make(int pc, int sd);
extern int piece(int p12);
extern int side(int p12);
extern int from_char(char c);
extern char to_char(int pc);
extern int from_fen(char c);
extern char to_fen(int p12);

}	// namespace piece

