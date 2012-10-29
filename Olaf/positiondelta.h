#ifndef POSITIONDELTA_H
#define POSITIONDELTA_H

class PositionDelta
{
public:
  typedef int_fast8_t d_row_t;

  typedef int_fast8_t d_column_t;

  PositionDelta(d_row_t, d_column_t);

  PositionDelta();

  d_row_t d_row() const;

  d_column_t d_column() const;

private:
  d_row_t m_d_row;

  d_column_t m_d_column;

};

#endif // POSITIONDELTA_H
