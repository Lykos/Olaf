#ifndef BITBOARD_H
#define BITBOARD_H

#include <array>
#include <cstdint>
#include <climits>
#include <ostream>

#include "olaf/rules/position.h"
#ifdef __POPCNT__
#include <popcntintrin.h>
#endif

namespace olaf
{

typedef uint64_t bitboard_t;

class BitBoard;

constexpr BitBoard operator |(BitBoard, BitBoard);

constexpr BitBoard operator ^(BitBoard, BitBoard);

constexpr BitBoard operator &(BitBoard, BitBoard);

constexpr BitBoard operator ~(BitBoard);

constexpr bool operator ==(BitBoard, BitBoard);

constexpr bool operator !=(BitBoard, BitBoard);

std::ostream& operator <<(std::ostream& out, const BitBoard bit_board);

/**
 * @brief The BitBoard class represents a board where a bit is stored in each square.
 */
class BitBoard
{
  friend constexpr BitBoard operator |(BitBoard, BitBoard);

  friend constexpr BitBoard operator ^(BitBoard, BitBoard);

  friend constexpr BitBoard operator &(BitBoard, BitBoard);

  friend constexpr BitBoard operator ~(BitBoard);

  friend constexpr bool operator ==(BitBoard, BitBoard);

  friend constexpr bool operator !=(BitBoard, BitBoard);

public:
  static const uint_fast8_t c_bitboard_size = Position::c_index_size;

  static_assert(sizeof(bitboard_t) * CHAR_BIT >= c_bitboard_size,
                "Not enough space for a bit board in the used type.");

  constexpr BitBoard(bitboard_t bits = 0): m_bits (bits) {}

  constexpr explicit BitBoard(const Position position): m_bits (1ull << position.index()) {}

  constexpr BitBoard operator -() const { return BitBoard(-m_bits); }

  constexpr operator bitboard_t() const { return m_bits; }

  static constexpr Position reverse_index(const uint_fast8_t index)
  {
    return Position(index / Position::c_column_size, index % Position::c_column_size);
  }

  constexpr bool get(const Position position) const
  {
    return m_bits & (1ULL << position.index());
  }

  inline void set(const Position position, bool value)
  {
    const uint_fast8_t i = position.index();
    m_bits = (m_bits & ~(1ULL << i)) | static_cast<bitboard_t>(value) << i;
  }

  BitBoard mirror_rows() const;

  inline uint_fast8_t number() const
  {
#ifdef __POPCNT__
    return _mm_popcnt_u64(m_bits);
#else
    static const bitboard_t m1  = 0x5555555555555555;
    static const bitboard_t m2  = 0x3333333333333333;
    static const bitboard_t m4  = 0x0f0f0f0f0f0f0f0f;
    static const bitboard_t h01 = 0x0101010101010101;

    bitboard_t x = m_bits;
    x -= (x >> 1) & m1;
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4;
    return (x * h01) >> 56;
#endif
  }

  inline BitBoard north_fill() const
  {
    bitboard_t bits = m_bits;
    bits |= bits << 8;
    bits |= bits << 16;
    bits |= bits << 32;
    return BitBoard(bits);
  }

  inline BitBoard south_fill() const
  {
    bitboard_t bits = m_bits;
    bits |= bits >> 8;
    bits |= bits >> 16;
    bits |= bits >> 32;
    return BitBoard(bits);
  }

  constexpr BitBoard one_up() const
  {
    return BitBoard(m_bits << 8);
  }

  constexpr BitBoard one_down() const
  {
    return BitBoard(m_bits >> 8);
  }

  constexpr BitBoard one_right() const
  {
    return BitBoard((m_bits & 0x7f7f7f7f7f7f7f7f) << 1);
  }

  constexpr BitBoard one_left() const
  {
    return BitBoard((m_bits & 0xfefefefefefefefe) >> 1);
  }

  /**
   * @brief first_position returns the position of the first set bit.
   */
  Position first_position() const;

  /**
   * @brief next_position returns the position of the first set bit like first_position.
   *        But it also unsets that bit and is hence useful for scanning.
   */
  Position next_position();

private:
  bitboard_t m_bits;
};

const BitBoard c_a_column(0x0101010101010101);
const BitBoard c_b_column(0x0202020202020202);
const BitBoard c_c_column(0x0404040404040404);
const BitBoard c_d_column(0x0808080808080808);
const BitBoard c_e_column(0x1010101010101010);
const BitBoard c_f_column(0x2020202020202020);
const BitBoard c_g_column(0x4040404040404040);
const BitBoard c_h_column(0x8080808080808080);

const std::array<BitBoard, Position::c_column_size> c_columns = {
  c_a_column,
  c_b_column,
  c_c_column,
  c_d_column,
  c_e_column,
  c_f_column,
  c_g_column,
  c_h_column
};

const BitBoard c_1_row(0xff);
const BitBoard c_2_row(0xff00);
const BitBoard c_3_row(0xff0000);
const BitBoard c_4_row(0xff000000);
const BitBoard c_5_row(0xff00000000);
const BitBoard c_6_row(0xff0000000000);
const BitBoard c_7_row(0xff000000000000);
const BitBoard c_8_row(0xff00000000000000);

const std::array<BitBoard, Position::c_row_size> c_rows = {
  c_1_row,
  c_2_row,
  c_3_row,
  c_4_row,
  c_5_row,
  c_6_row,
  c_7_row,
  c_8_row
};

constexpr BitBoard operator |(BitBoard a, BitBoard b)
{
  return BitBoard(a.m_bits | b.m_bits);
}

constexpr BitBoard operator ^(BitBoard a, BitBoard b)
{
  return BitBoard(a.m_bits ^ b.m_bits);
}

constexpr BitBoard operator &(BitBoard a, BitBoard b)
{
  return BitBoard(a.m_bits & b.m_bits);
}

constexpr BitBoard operator ~(BitBoard a)
{
  return BitBoard(~a.m_bits);
}

constexpr bool operator ==(BitBoard a, BitBoard b)
{
  return a.m_bits == b.m_bits;
}

constexpr bool operator !=(BitBoard a, BitBoard b)
{
  return a.m_bits != b.m_bits;
}

} // namespace olaf

#endif // BITBOARD_H
