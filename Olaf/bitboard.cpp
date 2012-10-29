#include "bitboard.h"

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

BitBoard operator==(const BitBoard& a, const BitBoard& b)
{
  return a.m_bits == b.m_bits;
}

uint_fast8_t index(const Position& position)
{
  return position.column() * Position::ROW_SIZE + position.row();
}

bool BitBoard::get(const Position& position) const
{
  return static_cast<bool>((m_bits << index(position)) & 1);
}

void BitBoard::set(const Position& position, bool value)
{
  m_bits |= static_cast<bits_t>(value) << index(position);
}

BitBoard BitBoard::mirror_rows() const
{
  bits_t bits = 0;
  static const bits_t row_mask = (1 << Position::COLUMN_SIZE) - 1;
  for (Position::row_t row = 0; row < Position::ROW_SIZE; ++row) {
    Position::row_t old_row = Position::ROW_SIZE - 1 - row;
    bits |= ((m_bits >> old_row * Position::COLUMN_SIZE) & row_mask) << row;
  }
  return BitBoard(bits);
}

