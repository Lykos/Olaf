#ifndef COLOR_H
#define COLOR_H

#include "position.h"
#include "positiondelta.h"

/**
 * @brief The Color enum represents the colors of the chess players. They are guaranteed
 * to be White = 0 and Black = 1, so they can be used as indices safely.
 */
enum Color {
  White = 0,
  Black = 1
};

constexpr Color next(Color color)
{
  return static_cast<Color>(1 - static_cast<uint_fast8_t>(color));
}

constexpr Color previous(Color color)
{
  return static_cast<Color>(1 - static_cast<uint_fast8_t>(color));
}

constexpr Position::row_t ground_line(Color color)
{
  return color == White ? 0 : 7;
}

constexpr PositionDelta forward_direction(Color color)
{
  return color == White ? PositionDelta(1, 0) : PositionDelta(-1, 0);
}

constexpr Position::row_t pawn_row(Color color)
{
  return color == White ? 1 : 6;
}

constexpr Position::row_t conversion_row(Color color)
{
  return color == White ? 7 : 0;
}

#endif // COLOR_H
