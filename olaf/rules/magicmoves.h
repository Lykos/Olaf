#ifndef MAGICMOVES_H
#define MAGICMOVES_H

#include "olaf/rules/bitboard.h"

namespace olaf
{

class ChessBoard;
class Position;

class MagicMoves
{
public:
  static BitBoard moves_rook(const Position& source, const ChessBoard& board);

  static BitBoard moves_bishop(const Position& source, const ChessBoard& board);

  static BitBoard moves_queen(const Position& source, const ChessBoard& board);

  static BitBoard moves_knight(const Position& source, const ChessBoard& board);

  static BitBoard moves_king(const Position& source, const ChessBoard& board);

  static BitBoard moves_pawn(const Position& source, const ChessBoard& board);
};

} // namespace

#endif // MAGICMOVES_H
