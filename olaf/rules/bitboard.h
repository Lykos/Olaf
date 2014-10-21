#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <climits>

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

constexpr bool operator ==(BitBoard, BitBoard);

constexpr bool operator !=(BitBoard, BitBoard);

/**
 * @brief The BitBoard class represents a board where a bit is stored in each square.
 */
class BitBoard
{
  friend constexpr BitBoard operator|(BitBoard, BitBoard);

  friend constexpr BitBoard operator^(BitBoard, BitBoard);

  friend constexpr BitBoard operator&(BitBoard, BitBoard);

  friend constexpr bool operator==(BitBoard, BitBoard);

  friend constexpr bool operator!=(BitBoard, BitBoard);

public:
  static const uint_fast8_t c_bitboard_size = Position::c_column_size * Position::c_row_size;

  static_assert(sizeof(bitboard_t) * CHAR_BIT >= c_bitboard_size,
                "Not enough space for a bit board in the used type.");

  constexpr BitBoard(bitboard_t bits = 0): m_bits (bits) {}

  constexpr BitBoard(const Position& position): m_bits (1ull << index(position)) {}

  /**
   * @brief index returns the index that has to be used to access the bit of this position
   * @param position
   * @return
   */
  static constexpr uint_fast8_t index(const Position& position)
  {
    return position.row() * Position::c_column_size + position.column();
  }

  static constexpr Position reverse_index(const uint_fast8_t index)
  {
    return Position(index / Position::c_column_size, index % Position::c_column_size);
  }

  constexpr bool get(const Position& position) const
  {
    return ((m_bits >> index(position)) & 1) != 0;
  }

  inline void set(const Position& position, bool value)
  {
    const uint_fast8_t i = index(position);
    m_bits = (m_bits & ~(1ull << i)) | static_cast<bitboard_t>(value) << i;
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

  Position first_position() const;

  std::vector<Position> positions() const;

private:
  bitboard_t m_bits;
};

constexpr BitBoard operator|(BitBoard a, BitBoard b)
{
  return BitBoard(a.m_bits | b.m_bits);
}

constexpr BitBoard operator^(BitBoard a, BitBoard b)
{
  return BitBoard(a.m_bits ^ b.m_bits);
}

constexpr BitBoard operator&(BitBoard a, BitBoard b)
{
  return BitBoard(a.m_bits & b.m_bits);
}

constexpr bool operator==(BitBoard a, BitBoard b)
{
  return a.m_bits == b.m_bits;
}

constexpr bool operator!=(BitBoard a, BitBoard b)
{
  return a.m_bits != b.m_bits;
}

} // namespace olaf

#endif // BITBOARD_H
