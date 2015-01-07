#ifndef MAGICNUMBERS_H
#define MAGICNUMBERS_H

#include <array>
#include <cstdint>
#include <vector>
#include <string>
#include <gflags/gflags.h>

#include "olaf/status.h"

DECLARE_string(move_table_file);

namespace olaf
{

struct Magic {
  const std::uint64_t* ptr;
  std::uint64_t mask;
  std::uint64_t magic;
  int shift;
};

class MagicNumbers
{
public:
  static const int c_move_table_size = 107648;

  static const int c_no_squares = 64;

  static void init();

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

  static const ColorTable c_castle_squares;

  static const ColorTable c_castle_k_room;

  static const ColorTable c_castle_q_room;

  static const ColorTable c_castle_k_rook_src;

  static const ColorTable c_castle_q_rook_src;

  static const ColorTable c_castle_k_rook_dst;

  static const ColorTable c_castle_q_rook_dst;

private:
  MagicNumbers();
  MagicNumbers(const MagicNumbers&) = delete;
  MagicNumbers(MagicNumbers&&) = delete;
  MagicNumbers& operator =(const MagicNumbers&) = delete;
  MagicNumbers& operator =(MagicNumbers&&) = delete;
};

} // namespace olaf

#endif // MAGICNUMBERS_H
