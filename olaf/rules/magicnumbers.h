#ifndef MAGICNUMBERS_H
#define MAGICNUMBERS_H

#include <array>
#include <vector>
#include <cstdint>

namespace olaf
{

struct Magic {
  const uint64_t* ptr;
  uint64_t mask;
  uint64_t magic;
  int shift;
};

struct MagicNumbers
{
  static const int c_move_table_size = 107648;

  typedef std::array<std::uint64_t, c_move_table_size> MoveTable;

  static const MoveTable c_move_table;

  static const int c_magic_table_size = 64;

  typedef std::array<Magic, c_magic_table_size> MagicTable;

  static const MagicTable c_rook_magic;

  static const MagicTable c_bishop_magic;
};

} // namespace olaf

#endif // MAGICNUMBERS_H
