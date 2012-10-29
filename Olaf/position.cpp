#include "position.h"

bool operator==(const Position& a, const Position& b)
{
  return a.m_column == b.m_column && a.m_row == b.m_row;
}

Position::row_t Position::row() const
{
  return m_row;
}

Position::column_t Position::column() const
{
  return m_column;
}

bool Position::in_bounds(const PositionDelta &d_pos) const
{
  PositionDelta::d_row_t row = static_cast<PositionDelta::d_row_t>(m_row) + d_pos.d_row();
  PositionDelta::d_column_t column = static_cast<PositionDelta::d_column_t>(m_column) + d_pos.d_column();
  return 0 <= row && row < ROW_SIZE && 0 <= column && column < COLUMN_SIZE;
}

Position operator+(const Position &pos, const PositionDelta &d_pos)
{
  return Position(pos.m_row + d_pos.m_d_row, pos.m_column + d_pos.m_d_column);
}

Position operator+(const PositionDelta &d_pos, const Position &pos)
{
  return operator+(pos, d_pos);
}
