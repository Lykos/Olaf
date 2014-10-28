#include "olaf/rules/magicmoves.h"

#include <array>

#include "olaf/rules/bitboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/magicnumbers.h"

using namespace std;

namespace olaf
{

static inline BitBoard internal_magic_moves(const array<Magic, BitBoard::c_bitboard_size>& magics,
                                            const Position& source,
                                            const BitBoard occupied)
{
  const Magic& magic = magics[BitBoard::index(source)];
  const uint64_t board = occupied;
  return magic.ptr[((board & magic.mask) * magic.magic) >> magic.shift];
}

// static
BitBoard MagicMoves::magic_moves_rook(const Position& source, const BitBoard occupied, const BitBoard friends)
{
  return internal_magic_moves(MagicNumbers::c_rook_magic, source, occupied) & BitBoard(~friends);
}

// static
BitBoard MagicMoves::magic_moves_bishop(const Position& source, const BitBoard occupied, const BitBoard friends)
{
  return internal_magic_moves(MagicNumbers::c_bishop_magic, source, occupied) & BitBoard(~friends);
}

// static
BitBoard MagicMoves::magic_moves_queen(const Position& source, const BitBoard occupied, const BitBoard friends)
{
  return (internal_magic_moves(MagicNumbers::c_rook_magic, source, occupied)
      | internal_magic_moves(MagicNumbers::c_bishop_magic, source, occupied)) & BitBoard(~friends);
}

} // namespace
