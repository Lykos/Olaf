#include "oncepiece.h"

using namespace std;

OncePiece::OncePiece(const std::vector<PositionDelta> &directions):
  m_directions (directoins)
{}

vector<Move> OncePiece::moves(const Position &source, const BitBoard &opponents, const BitBoard &friends) const
{
  vector<Move> result;
  for (auto it = m_directions.begin(); it < m_directions.end(); ++it) {
    if (position.in_bounds(*it)) {
      Position destination = position + *it;

    }
  }
  return result;
}
