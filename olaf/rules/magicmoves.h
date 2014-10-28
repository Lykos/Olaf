#ifndef MAGICMOVES_H
#define MAGICMOVES_H

#include "olaf/rules/bitboard.h"
#include "olaf/rules/position.h"

namespace olaf
{

class MagicMoves
{
public:
  static BitBoard magic_moves_rook(const Position& source, const BitBoard occupied, const BitBoard friends);

  static BitBoard magic_moves_bishop(const Position& source, const BitBoard occupied, const BitBoard friends);

  static BitBoard magic_moves_queen(const Position& source, const BitBoard occupied, const BitBoard friends);
};

} // namespace

#endif // MAGICMOVES_H
