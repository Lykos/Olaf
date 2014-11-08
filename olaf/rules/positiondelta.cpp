#include "olaf/rules/positiondelta.h"

using namespace std;

namespace olaf
{

PositionDelta operator+(const PositionDelta &a, const PositionDelta &b)
{
  return PositionDelta(a.m_d_row + b.m_d_row, a.m_d_column + b.m_d_column);
}

bool operator==(const PositionDelta &a, const PositionDelta &b)
{
  return a.m_d_row == b.m_d_row && a.m_d_column == b.m_d_column;
}

PositionDelta PositionDelta::unit() const
{
  const d_row_t length = max(abs(m_d_row), abs(m_d_column));
  if (length == 0) {
    return *this;
  }
  if (m_d_row % length != 0 || m_d_column % length != 0) {
    // Not possible
    return *this;
  }
  return PositionDelta(m_d_row / length, m_d_column / length);
 }

} // namespace olaf
