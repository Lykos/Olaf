#ifndef POSITION_H
#define POSITION_H

#include <cstdint>

class Position;

bool operator==(const Position&, const Position&);

/**
 * @brief The Position class represents the coordinates of one particular square of the board.
 */
class Position
{
  friend bool operator==(const Position&, const Position&);

public:
  typedef std::uint_fast8_t row_t;

  typedef std::uint_fast8_t column_t;

  static const row_t ROW_SIZE = 8;

  static const column_t COLUMN_SIZE = 8;

  /**
   * @brief Position
   * @param row has to fulfill 0 <= row < ROW_SIZE
   * @param column has to fulfill 0 <= column < COLUMN_SIZE
   */
  Position(row_t row, column_t column);

  /**
   * @brief Position with row = column = 0
   */
  Position();

  row_t row() const;

  column_t column() const;

private:
  row_t m_row;

  column_t m_column;

};

#endif // POSITION_H
