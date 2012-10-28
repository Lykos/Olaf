#include "bitboard.h"

BitBoard operator|(BitBoard a, BitBoard b)
{
  return BitBoard(a.m_bits | b.m_bits);
}

BitBoard operator^(BitBoard a, BitBoard b)
{
  return BitBoard(a.m_bits ^ b.m_bits);
}

BitBoard operator&(BitBoard a, BitBoard b)
{
  return BitBoard(a.m_bits & b.m_bits);
}

BitBoard::BitBoard(uint64_t bits):
  m_bits (bits)
{}

bool get(Position position)
{
  uint_fast8_t index = position.row() * COLUMN_SIZE + position.row();
  static_cast<bool>((m_bits << index) & 1);
}

bool set(Position, bool);
