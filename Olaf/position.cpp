#include "position.h"

bool operator==(const Position& a, const Position& b)
{
  return a.m_column == b.m_column && a.m_row == b.m_row;
}

Position::Position(row_t row, column_t column):
  m_row (row),
  m_column (column)
{}

Position::Position()
{}

Position::row_t Position::row() const
{
  return m_row;
}

Position::column_t Position::column() const
{
  return m_column;
}
