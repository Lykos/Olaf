#ifndef POSITION_H
#define POSITION_H

#include <cstdint>
#include <ostream>
#include <istream>
#include <vector>
#include <string>

namespace olaf
{

class Position;

std::ostream& operator<<(std::ostream& out, Position position);

std::istream& operator>>(std::istream& in, Position& position);

constexpr bool operator==(Position left, Position right);

constexpr bool operator<(Position left, Position right);

/**
 * @brief The Position class represents the coordinates of one particular square of the board.
 */
class Position
{
  friend std::ostream& operator<<(std::ostream& out, Position position);

  friend std::istream& operator>>(std::istream& in, Position& position);

  friend constexpr bool operator==(Position left, Position right);

  friend constexpr bool operator<(Position left, Position right);

public:
  typedef std::int_fast8_t index_t;

  static const index_t c_row_size = 8;
  static const index_t c_column_size = 8;
  static const index_t c_index_size = c_row_size * c_column_size;

  static const index_t c_queens_rook_column = 0;
  static const index_t c_queens_knight_column = 1;
  static const index_t c_queens_bishop_column = 2;
  static const index_t c_queen_column = 3;
  static const index_t c_king_column = 4;
  static const index_t c_kings_bishop_column = 5;
  static const index_t c_kings_knight_column = 6;
  static const index_t c_kings_rook_column = 7;

  static const std::string columns;

  static const std::string rows;

  /**
   * @brief positions returns all valid positions on the board in the order
   *        a8, b8, ..., h8, a7, b7, ...
   */
  static const std::vector<Position>& all_positions();

  /**
   * @brief Position
   * @param row has to fulfill 0 <= row < ROW_SIZE
   * @param column has to fulfill 0 <= column < COLUMN_SIZE
   */
  constexpr Position(index_t row, index_t column): m_index(row * c_column_size + column) {}

  /**
   * @brief Position with row = column = 0
   */
  constexpr Position(): Position(0) {}

  explicit Position(const std::string& pos);

  constexpr explicit Position(const index_t index): m_index(index) {}

  constexpr index_t row() const { return m_index / c_column_size; }

  constexpr index_t column() const { return m_index % c_column_size; }

  constexpr index_t index() const { return m_index; }

private:
  index_t m_index;
};

constexpr bool operator==(const Position left, const Position right)
{
  return left.m_index == right.m_index;
}

constexpr bool operator<(const Position left, const Position right)
{
  return left.m_index < right.m_index;
}

} // namespace olaf

#endif // POSITION_H
