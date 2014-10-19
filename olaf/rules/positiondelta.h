#ifndef POSITIONDELTA_H
#define POSITIONDELTA_H

#include <cstdint>

namespace olaf
{

class Position;
class PositionDelta;

Position operator+(const Position&, const PositionDelta&);

Position operator+(const PositionDelta&, const Position&);

PositionDelta operator+(const PositionDelta&, const PositionDelta&);

bool operator==(const PositionDelta&, const PositionDelta&);

class PositionDelta
{
  friend Position operator+(const Position&, const PositionDelta&);

  friend Position operator+(const PositionDelta&, const Position&);

  friend PositionDelta operator+(const PositionDelta&, const PositionDelta&);

  friend bool operator==(const PositionDelta&, const PositionDelta&);

public:
  typedef std::int_fast8_t d_row_t;

  typedef std::int_fast8_t d_column_t;

  constexpr PositionDelta(d_row_t d_row, d_column_t d_column): m_d_row (d_row), m_d_column (d_column) {}

  constexpr PositionDelta(): PositionDelta(0, 0) {}

  constexpr d_row_t d_row() const { return m_d_row; }

  constexpr d_column_t d_column() const { return m_d_column; }

private:
  const d_row_t m_d_row;

  const d_column_t m_d_column;
};

} // namespace olaf

#include "olaf/rules/position.h"

#endif // POSITIONDELTA_H
