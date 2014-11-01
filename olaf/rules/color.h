#ifndef COLOR_H
#define COLOR_H

#include <array>
#include <cstdint>

#include "olaf/rules/position.h"

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

const std::uint_fast8_t c_no_colors = 2;

const std::array<Color, c_no_colors> c_colors = {Color::White, Color::Black};

constexpr Color other_color(Color color)
{
  return static_cast<Color>(1 - static_cast<uint_fast8_t>(color));
}

constexpr Position::index_t ground_line(Color color)
{
  return color == Color::White ? 0 : 7;
}

constexpr Position::index_t pawn_row(Color color)
{
  return color == Color::White ? 1 : 6;
}

constexpr Position::index_t promotion_row(Color color)
{
  return color == Color::White ? 7 : 0;
}

} // namespace olaf

#endif // COLOR_H
