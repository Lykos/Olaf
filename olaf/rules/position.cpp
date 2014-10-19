#include "olaf/rules/position.h"

#include <cassert>
#include <cctype>
#include <sstream>

#include "olaf/rules/positiondelta.h"

using namespace std;

namespace olaf
{

static vector<Position> generate_all_positions()
{
  vector<Position> result;
  for (Position::row_t row = Position::c_row_size - 1; row >= 0; --row) {
    for (Position::column_t column = 0; column < Position::c_column_size; ++column) {
      result.emplace_back(row, column);
    }
  }
  return result;
}

const std::string Position::rows = "12345678";

const std::string Position::columns = "abcdefgh";

std::ostream& operator<<(std::ostream& out, const Position& position)
{
  assert(0 <= position.m_column && position.m_column < Position::c_column_size);
  assert(0 <= position.m_row && position.m_row < Position::c_row_size);
  return out << Position::columns[position.column()] << Position::rows[position.row()];
}

std::istream& operator>>(std::istream& in, Position& position)
{
  while (isspace(in.peek())) {
    in.get();
  }
  char column = in.get();
  char row = in.get();
  position = Position(Position::rows.find(row), Position::columns.find(column));
  return in;
}

bool operator==(const Position& a, const Position& b)
{
  return a.m_column == b.m_column && a.m_row == b.m_row;
}

bool operator<(const Position& a, const Position& b)
{
  if (a.m_column != b.m_column) {
    return a.m_column < b.m_column;
  } else {
    return a.m_row < b.m_row;
  }
}

const vector<Position>& Position::all_positions()
{
  static const vector<Position> positions = generate_all_positions();
  return positions;
}

PositionDelta operator-(const Position& a, const Position& b)
{
  PositionDelta::d_row_t d_row = static_cast<PositionDelta::d_row_t>(a.m_row) - static_cast<PositionDelta::d_row_t>(b.m_row);
  PositionDelta::d_column_t d_column = static_cast<PositionDelta::d_column_t>(a.m_column) - static_cast<PositionDelta::d_column_t>(b.m_column);
  return PositionDelta(d_row, d_column);
}

Position::Position(const string &pos)
{
  istringstream iss(pos);
  iss >> *this;
}

bool Position::in_bounds(const PositionDelta& d_pos) const
{
  PositionDelta::d_row_t row = static_cast<PositionDelta::d_row_t>(m_row) + d_pos.d_row();
  PositionDelta::d_column_t column = static_cast<PositionDelta::d_column_t>(m_column) + d_pos.d_column();
  return 0 <= row && row < c_row_size && 0 <= column && column < c_column_size;
}

Position operator+(const Position &pos, const PositionDelta &d_pos)
{
  return Position(pos.m_row + d_pos.m_d_row, pos.m_column + d_pos.m_d_column);
}

Position operator+(const PositionDelta &d_pos, const Position &pos)
{
  return operator+(pos, d_pos);

} // namespace olaf
}
