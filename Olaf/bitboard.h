#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include "position.h"

class BitBoard;

BitBoard operator|(BitBoard, BitBoard);

BitBoard operator^(BitBoard, BitBoard);

BitBoard operator&(BitBoard, BitBoard);

/**
 * @brief The BitBoard class represents a board where a bit is stored in each square.
 */
class BitBoard
{
  friend BitBoard operator|(BitBoard, BitBoard);

  friend BitBoard operator^(BitBoard, BitBoard);

  friend BitBoard operator&(BitBoard, BitBoard);

public:
  BitBoard(uint64_t);

  bool get(Position);

  bool set(Position, bool);

  static const uint_fast8_t ROW_SIZE = 8;

  static const uint_fast8_t COLUMN_SIZE = 8;

private:
  uint64_t m_bits;
};

#endif // BITBOARD_H
