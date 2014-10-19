#include "bitboard.h"
#ifdef __POPCNT__
#include <popcntintrin.h>
#endif

using namespace std;

BitBoard operator|(const BitBoard& a, const BitBoard& b)
{
  return BitBoard(a.m_bits | b.m_bits);
}

BitBoard operator^(const BitBoard& a, const BitBoard& b)
{
  return BitBoard(a.m_bits ^ b.m_bits);
}

BitBoard operator&(const BitBoard& a, const BitBoard& b)
{
  return BitBoard(a.m_bits & b.m_bits);
}

bool operator==(const BitBoard& a, const BitBoard& b)
{
  return a.m_bits == b.m_bits;
}

uint_fast8_t index(const Position& position)
{
  return position.row() * Position::c_column_size + position.column();
}

Position reverse_index(const uint_fast8_t index)
{
  return Position(index / Position::c_column_size, index % Position::c_column_size);
}

bool BitBoard::get(const Position& position) const
{
  return static_cast<bool>((m_bits >> index(position)) & 1);
}

void BitBoard::set(const Position& position, bool value)
{
  if (value) {
    m_bits |= 1ull << index(position);
  } else {
    m_bits &= ~(1ull << index(position));
  }
}

BitBoard BitBoard::mirror_rows() const
{
  bitboard_t bits = 0;
  static const bitboard_t row_mask = (1 << Position::c_column_size) - 1;
  for (Position::row_t row_index = 0; row_index < Position::c_row_size; ++row_index) {
    Position::row_t old_row_index = Position::c_column_size - 1 - row_index;
    bitboard_t old_row_content = (m_bits >> old_row_index * Position::c_column_size) & row_mask;
    bits |= old_row_content << row_index * Position::c_column_size;
  }
  return BitBoard(bits);
}

static const uint_fast8_t index64[64] = {
    0,  1, 48,  2, 57, 49, 28,  3,
   61, 58, 50, 42, 38, 29, 17,  4,
   62, 55, 59, 36, 53, 51, 43, 22,
   45, 39, 33, 30, 24, 18, 12,  5,
   63, 47, 56, 27, 60, 41, 37, 16,
   54, 35, 52, 21, 44, 32, 23, 11,
   46, 26, 40, 15, 34, 20, 31, 10,
   25, 14, 19,  9, 13,  8,  7,  6
};

static uint_fast8_t bit_scan(const bitboard_t bits)
{
  const bitboard_t debruijn64 = 0x03f79d71b4cb0a89ull;
  return index64[((bits & -bits) * debruijn64) >> 58];
}

vector<Position> BitBoard::positions() const
{
  vector<Position> result;
  bitboard_t bits = m_bits;
  while (bits) {
    result.emplace_back(reverse_index(bit_scan(bits)));
    bits &= bits - 1;
  }
  return result;
}

#ifdef __POPCNT__

uint_fast8_t BitBoard::number() const
{
  return _mm_popcnt_u64(m_bits);
}

#else
static const bitboard_t m1  = 0x5555555555555555;
static const bitboard_t m2  = 0x3333333333333333;
static const bitboard_t m4  = 0x0f0f0f0f0f0f0f0f;
static const bitboard_t h01 = 0x0101010101010101;

uint_fast8_t BitBoard::number() const
{
  bitboard_t x = m_bits;
  x -= (x >> 1) & m1;
  x = (x & m2) + ((x >> 2) & m2);
  x = (x + (x >> 4)) & m4;
  return (x * h01) >> 56;
}
#endif
