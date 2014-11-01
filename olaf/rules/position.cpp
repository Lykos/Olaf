#include "olaf/rules/position.h"

#include <cassert>
#include <cctype>
#include <sstream>

using namespace std;

namespace olaf
{

static vector<Position> generate_all_positions()
{
  vector<Position> result;
  for (Position::index_t row = Position::c_row_size - 1; row >= 0; --row) {
    for (Position::index_t column = 0; column < Position::c_column_size; ++column) {
      result.emplace_back(row, column);
    }
  }
  return result;
}

const std::string Position::rows = "12345678";

const std::string Position::columns = "abcdefgh";

std::ostream& operator<<(std::ostream& out, const Position position)
{
  assert(0 <= position.m_index && position.m_index < Position::c_index_size);
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

const vector<Position>& Position::all_positions()
{
  static const vector<Position> positions = generate_all_positions();
  return positions;
}

Position::Position(const string& pos)
{
  istringstream iss(pos);
  iss >> *this;
}

} // namespace olaf
