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

BitBoard::BitBoard(uint64_t bits):
  m_bits (bits)
{}

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
  m_bits |= static_cast<uint64_t>(value) << index(position);
}
