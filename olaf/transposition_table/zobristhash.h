#ifndef ZOBRISTHASH_H
#define ZOBRISTHASH_H

#include <cstdint>

#include "olaf/rules/piece.h"
#include "olaf/transposition_table/hashstate.h"

namespace olaf
{

enum class Color;
class ChessBoard;
class Position;

class ZobristHash
{
public:
  typedef HashState::hash_t hash_t;

  static void calculate(const ChessBoard& board, HashState* state);

  static void update(Color color,
                     Piece::piece_index_t piece_index,
                     Position position,
                     HashState* state);

  static void update_castle_k(Color color, HashState* state);

  static void update_castle_q(Color color, HashState* state);

  static void update_ep(Position position, HashState* state);

  static void update_turn_color(HashState* state);
};

}  // namespace olaf

#endif // ZOBRISTHASH_H
