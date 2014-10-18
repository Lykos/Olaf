#ifndef POSITION_H
#define POSITION_H

#include "positiondelta.h"
#include <cstdint>
#include <ostream>
#include <istream>
#include <string>

class Position;

std::ostream& operator<<(std::ostream &out, const Position &position);

std::istream& operator>>(std::istream &in, Position &position);

bool operator==(const Position& left, const Position& right);

bool operator<(const Position& left, const Position& right);

PositionDelta operator-(const Position&, const Position&);

/**
 * @brief The Position class represents the coordinates of one particular square of the board.
 */
class Position
{
  friend std::ostream& operator<<(std::ostream &out, const Position &position);

  friend std::istream& operator>>(std::istream &in, Position &position);

  friend bool operator==(const Position& left, const Position& right);

  friend bool operator<(const Position& left, const Position& right);

  friend Position operator+(const Position&, const PositionDelta&);

  friend Position operator+(const PositionDelta&, const Position&);

  friend PositionDelta operator-(const Position&, const Position&);

public:
  typedef std::int_fast8_t row_t;

  typedef std::int_fast8_t column_t;

  static const row_t c_row_size = 8;

  static const column_t c_column_size = 8;

  static const column_t c_queens_rook_column = 0;
  static const column_t c_queens_knight_column = 1;
  static const column_t c_queens_bishop_column = 2;
  static const column_t c_queen_column = 3;
  static const column_t c_king_column = 4;
  static const column_t c_kings_bishop_column = 5;
  static const column_t c_kings_knight_column = 6;
  static const column_t c_kings_rook_column = 7;

  static const std::string columns;

  static const std::string rows;

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

  explicit Position(const std::string& pos);

  constexpr row_t row() const { return m_row; }

  constexpr column_t column() const { return m_column; }

  bool in_bounds(const PositionDelta& d_pos) const;

private:
  row_t m_row;

  column_t m_column;
};

#endif // POSITION_H
