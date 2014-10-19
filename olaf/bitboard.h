#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <climits>

#include "position.h"

namespace olaf
{

typedef uint64_t bitboard_t;
static_assert(sizeof(bitboard_t) * CHAR_BIT >= Position::c_column_size * Position::c_row_size,
              "Not enough space for a bit board in the used type.");

class BitBoard;

BitBoard operator|(const BitBoard&, const BitBoard&);

BitBoard operator^(const BitBoard&, const BitBoard&);

BitBoard operator&(const BitBoard&, const BitBoard&);

bool operator==(const BitBoard&, const BitBoard&);

bool operator==(const BitBoard&, bitboard_t);

bool operator==(bitboard_t, const BitBoard&);

/**
 * @brief The BitBoard class represents a board where a bit is stored in each square.
 */
class BitBoard
{
  friend BitBoard operator|(const BitBoard&, const BitBoard&);

  friend BitBoard operator^(const BitBoard&, const BitBoard&);

  friend BitBoard operator&(const BitBoard&, const BitBoard&);

  friend bool operator==(const BitBoard&, const BitBoard&);

  friend bool operator==(const BitBoard&, uint64_t);

  friend bool operator==(uint64_t, const BitBoard&);

public:
  constexpr explicit BitBoard(bitboard_t bits = 0): m_bits (bits) {}

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

} // namespace olaf

#endif // BITBOARD_H
