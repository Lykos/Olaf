#include "olaf/rules/pieceboard.h"

using namespace std;

namespace olaf
{

bool operator ==(const PieceBoard& left, const PieceBoard& right)
{
  if (&left == &right) {
    return true;
  }
  return left.m_piece == right.m_piece
      && left.m_bit_board == right.m_bit_board;
}

} // namespace olaf
