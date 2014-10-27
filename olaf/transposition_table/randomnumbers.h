#ifndef RANDOMNUMBERS_H
#define RANDOMNUMBERS_H

#include <array>
#include <cstdint>

namespace olaf
{

struct RandomNumbers {
  // We intentionally redefine all these values s.t. we don't depend on any headers and have to recompile
  // this file.

  static const int c_no_colors = 2;

  static const int c_no_pieces = 6;

  static const int c_no_squares = 64;

  static const std::array<std::uint64_t, c_no_colors * c_no_pieces * c_no_squares> c_piece_randomness;

  static const std::array<std::uint64_t, c_no_colors> c_castle_k_randomness;

  static const std::array<std::uint64_t, c_no_colors> c_castle_q_randomness;

  static const std::array<std::uint64_t, c_no_squares> c_ep_randomness;

  static const std::uint64_t c_turn_color_randomness;
};

}  // namespace olaf

#endif // RANDOMNUMBERS_H
