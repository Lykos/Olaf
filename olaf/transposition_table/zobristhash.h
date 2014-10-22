#ifndef ZOBRISTHASH_H
#define ZOBRISTHASH_H

#include <cstdint>

#include "olaf/rules/piece.h"

namespace olaf
{

enum class Color;
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

  static void update_castle_k(Color color, ChessBoard* board);

  static void update_castle_q(Color color, ChessBoard* board);

  static void update_ep(const Position& position, ChessBoard* board);

  static void update_turn_color(ChessBoard* board);
};

}  // namespace olaf

#endif // ZOBRISTHASH_H
