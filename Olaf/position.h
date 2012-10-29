#ifndef POSITION_H
#define POSITION_H

#include <cstdint>
#include "positiondelta.h"

class Position;

bool operator==(const Position&, const Position&);

/**
 * @brief The Position class represents the coordinates of one particular square of the board.
 */
class Position
{
  friend bool operator==(const Position&, const Position&);

  friend Position operator+(const Position&, const PositionDelta&);

  friend Position operator+(const PositionDelta&, const Position&);

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
  constexpr Position(row_t row, column_t column): m_row (row), m_column (column) {}

  /**
   * @brief Position with row = column = 0
   */
  constexpr Position(): Position(0, 0) {}

  row_t row() const;

  column_t column() const;

  bool in_bounds(const PositionDelta&) const;

private:
  row_t m_row;

  column_t m_column;

};

#endif // POSITION_H
