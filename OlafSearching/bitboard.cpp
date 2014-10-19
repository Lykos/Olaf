#include "bitboard.h"

#ifdef __POPCNT__
#include <popcntintrin.h>
#endif

using namespace std;

namespace olaf
{

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

bool operator==(const BitBoard& a, const bitboard_t b)
{
  return a.m_bits == b;
}

bool operator==(const bitboard_t a, const BitBoard& b)
{
  return a == b.m_bits;
}

uint_fast8_t index(const Position& position)
{
  return position.row() * Position::c_column_size + position.column();
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

#ifdef __POPCNT__

uint_fast8_t BitBoard::number() const
{
  return _mm_popcnt_u64(m_bits);
}

#else
const bitboard_t m1  = 0x5555555555555555;
const bitboard_t m2  = 0x3333333333333333;
const bitboard_t m4  = 0x0f0f0f0f0f0f0f0f;
const bitboard_t h01 = 0x0101010101010101;

uint_fast8_t BitBoard::number() const
{
  bitboard_t x = m_bits;
  x -= (x >> 1) & m1;
  x = (x & m2) + ((x >> 2) & m2);
  x = (x + (x >> 4)) & m4;
  return (x * h01) >> 56;
}

#endif

} // namespace olaf
