#include "positiondelta.h"

using namespace std;

PositionDelta::d_row_t PositionDelta::d_row() const
{
  return m_d_row;
}

PositionDelta::d_column_t PositionDelta::d_column() const
{
  return m_d_column;
}

PositionDelta operator+(const PositionDelta &a, const PositionDelta &b)
{
  return PositionDelta(a.m_d_row + b.m_d_row, a.m_d_column + b.m_d_column);
}
