#ifndef COLOR_H
#define COLOR_H

#include "olaf/rules/position.h"
#include "olaf/rules/positiondelta.h"

namespace olaf
{

/**
 * @brief The Color enum represents the colors of the chess players. They are guaranteed
 * to be White = 0 and Black = 1, so they can be used as indices safely.
 */
enum class Color {
  White = 0,
  Black = 1
};

constexpr Color other_color(Color color)
{
  return static_cast<Color>(1 - static_cast<uint_fast8_t>(color));
}

constexpr Position::row_t ground_line(Color color)
{
  return color == Color::White ? 0 : 7;
}

constexpr PositionDelta forward_direction(Color color)
{
  return color == Color::White ? PositionDelta(1, 0) : PositionDelta(-1, 0);
}

constexpr Position::row_t pawn_row(Color color)
{
  return color == Color::White ? 1 : 6;
}

constexpr Position::row_t promotion_row(Color color)
{
  return color == Color::White ? 7 : 0;
}

} // namespace olaf

#endif // COLOR_H
