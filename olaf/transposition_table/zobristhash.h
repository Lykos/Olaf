#ifndef ZOBRISTHASH_H
#define ZOBRISTHASH_H

#include <cstdint>

#include "olaf/rules/piece.h"
#include "olaf/rules/color.h"

namespace olaf
{

class ChessBoard;
class Position;

class ZobristHash
{
public:
  typedef std::uint64_t hash_t;

  static void calculate(ChessBoard* board);

  static void update(Color color,
                     Piece::piece_index_t piece_index,
                     const Position& position,
                     ChessBoard* board);
};

}  // namespace olaf

#endif // ZOBRISTHASH_H
