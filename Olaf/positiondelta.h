#ifndef POSITIONDELTA_H
#define POSITIONDELTA_H

#include <cstdint>

class Position;
class PositionDelta;

Position operator+(const Position&, const PositionDelta&);
Position operator+(const PositionDelta&, const Position&);
PositionDelta operator+(const PositionDelta&, const PositionDelta&);

class PositionDelta
{
  friend Position operator+(const Position&, const PositionDelta&);

  friend Position operator+(const PositionDelta&, const Position&);

  friend PositionDelta operator+(const PositionDelta&, const PositionDelta&);

public:
  typedef std::int_fast8_t d_row_t;

  typedef std::int_fast8_t d_column_t;

  constexpr PositionDelta(d_row_t d_row, d_column_t d_column): m_d_row (d_row), m_d_column (d_column) {}

  constexpr PositionDelta(): PositionDelta(0, 0) {}

  d_row_t d_row() const;

  d_column_t d_column() const;

private:
  d_row_t m_d_row;

  d_column_t m_d_column;

};

#endif // POSITIONDELTA_H
