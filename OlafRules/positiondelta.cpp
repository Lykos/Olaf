#include "positiondelta.h"

using namespace std;

PositionDelta operator+(const PositionDelta &a, const PositionDelta &b)
{
  return PositionDelta(a.m_d_row + b.m_d_row, a.m_d_column + b.m_d_column);
}

bool operator==(const PositionDelta &a, const PositionDelta &b)
{
  return a.m_d_row == b.m_d_row && a.m_d_column == b.m_d_column;
}
