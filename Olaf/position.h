#ifndef POSITION_H
#define POSITION_H

#include <cstdint>

/**
 * @brief The Position class represents the coordinates of one particular square of the board.
 */
class Position
{
public:
  typedef uint8_fast_t row_t;

  typedef uint8_fast_t column_t;

  Position(row_t row, column_t column);

  row_t row() const;

  column_t column() const;

private:
  row_t m_row;

  column_t m_column;

};

#endif // POSITION_H
