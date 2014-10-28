#ifndef MAGICNUMBERS_H
#define MAGICNUMBERS_H

#include <array>
#include <vector>
#include <cstdint>

namespace olaf
{

struct Magic {
  const std::uint64_t* ptr;
  std::uint64_t mask;
  std::uint64_t magic;
  int shift;
};

struct MagicNumbers
{
  static const int c_move_table_size = 107648;

  typedef std::array<std::uint64_t, c_move_table_size> MoveTable;

  static const MoveTable c_move_table;

  static const int c_no_squares = 64;

  typedef std::array<Magic, c_no_squares> MagicTable;

  static const MagicTable c_rook_magic;

  static const MagicTable c_bishop_magic;

  typedef std::array<std::uint64_t, c_no_squares> SquareTable;

  static const SquareTable c_knight_table;

  static const SquareTable c_king_table;

  static const int c_no_colors = 2;

  typedef std::array<std::uint64_t, c_no_colors * c_no_squares> ColorSquareTable;

  static const ColorSquareTable c_pawn_one_step_table;

  static const ColorSquareTable c_pawn_two_step_table;

  static const ColorSquareTable c_pawn_capture_table;

  typedef std::array<std::uint64_t, c_no_colors> ColorTable;

  static const ColorTable c_promotion_rows;

  static const ColorTable c_king_positions;

  static const ColorTable c_castle_k_square;

  static const ColorTable c_castle_q_square;

  static const ColorTable c_castle_k_room;

  static const ColorTable c_castle_q_room;

  static const ColorTable c_castle_k_rook;

  static const ColorTable c_castle_q_rook;
};

} // namespace olaf

#endif // MAGICNUMBERS_H
