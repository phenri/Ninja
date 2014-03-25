#pragma once
#include <string>

namespace side {

enum {WHITE, BLACK, SIZE};

int opposite(int sd);

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

int make(int fl, int rk);
int make(int fl, int rk, int sd);
int file(int sq);
int rank(int sq);
int rank(int sq, int sd);
int opposit_file(int sq);
int opposit_rank(int sq);
bool is_promotion(int sq);
int color(int sq);
bool same_color(int s0, int s1);
bool same_line(int s0, int s1);
int file_distance(int s0, int s1);
int rank_distance(int s0, int s1);
int distance(int s0, int s1);
int pawn_inc(int sd);
int stop(int sq, int sd);
int promotion(int sq, int sd);

bool is_valid_88(int s88);
int to_88(int sq);
int from_88(int s88);

int from_fen(int sq);
int from_string(const std::string & s);
std::string to_string(int sq);

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

bool is_minor(int pc);
bool is_major(int pc);
bool is_slider(int pc);
int score(int pc);
int value(int pc);
int make(int pc, int sd);
int piece(int p12);
int side(int p12);
int from_char(char c);
char to_char(int pc);
int from_fen(char c);
char to_fen(int p12);

}	// namespace piece

