#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <climits>
#include "position.h"

class BitBoard;

BitBoard operator|(const BitBoard&, const BitBoard&);

BitBoard operator^(const BitBoard&, const BitBoard&);

BitBoard operator&(const BitBoard&, const BitBoard&);

bool operator==(const BitBoard&, const BitBoard&);

typedef uint64_t bitboard_t;
static_assert(sizeof(bitboard_t) * CHAR_BIT >= Position::COLUMN_SIZE * Position::ROW_SIZE,
              "Not enough space for a bit board in the used type.");

/**
 * @brief The BitBoard class represents a board where a bit is stored in each square.
 */
class BitBoard
{
  friend BitBoard operator|(const BitBoard&, const BitBoard&);

  friend BitBoard operator^(const BitBoard&, const BitBoard&);

  friend BitBoard operator&(const BitBoard&, const BitBoard&);

  friend bool operator==(const BitBoard&, const BitBoard&);

public:
  constexpr BitBoard(bitboard_t bits = 0): m_bits (bits) {}

  bool get(const Position&) const;

  void set(const Position&, bool);

  BitBoard mirror_rows() const;

  std::uint_fast8_t number() const;

private:

  bitboard_t m_bits;
};

/**
 * @brief index returns the index that has to be used to access the bit of this position
 * @param position
 * @return
 */
std::uint_fast8_t index(const Position& position);

#endif // BITBOARD_H