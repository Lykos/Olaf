#include "position.h"

Position::Position(row_t row, column_t column):
  m_row (row),
  m_column (column)
{}

Position::row_t Position::row() const
{
  return m_row;
}

Position::column_t Position::column() const
{
  return m_column;
}
