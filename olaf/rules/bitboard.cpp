#include "olaf/rules/bitboard.h"

using namespace std;

namespace olaf
{

BitBoard BitBoard::mirror_rows() const
{
  bitboard_t bits = 0;
  static const bitboard_t row_mask = (1 << Position::c_column_size) - 1;
  for (Position::index_t row_index = 0; row_index < Position::c_row_size; ++row_index) {
    const Position::index_t old_row_index = Position::c_column_size - 1 - row_index;
    bitboard_t old_row_content = (m_bits >> old_row_index * Position::c_column_size) & row_mask;
    bits |= old_row_content << row_index * Position::c_column_size;
  }
  return BitBoard(bits);
}

static inline uint_fast8_t bit_scan(const bitboard_t bits)
{
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
  const bitboard_t debruijn64 = 0x03f79d71b4cb0a89ull;
  return index64[((bits & -bits) * debruijn64) >> 58];
}

Position BitBoard::first_position() const
{
  return reverse_index(m_bits ? bit_scan(m_bits) : 0);
}

Position BitBoard::next_position()
{
  Position result(reverse_index(bit_scan(m_bits)));
  m_bits &= m_bits - 1;
  return result;
}

ostream& operator <<(ostream& out, const BitBoard bit_board)
{
  for (Position::index_t row = 7; row >= 0; --row) {
    for (Position::index_t column = 0; column < 8; ++column) {
      out << (bit_board.get(Position(row, column)) ? 1 : 0);
    }
    out << endl;
  }
  return out;
}

} // namespace olaf
