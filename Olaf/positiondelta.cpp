#include "positiondelta.h"

PositionDelta::PositionDelta(d_row_t d_row, d_column_t d_column):
  m_d_row (d_row),
  m_d_column (d_column)
{}

PositionDelta::PositionDelta():
  PositionDelta(0, 0)
{}

d_row_t PositionDelta::d_row() const
{
  return m_d_row;
}

d_column_t PositionDelta::d_column() const
{
  return m_d_column;
}
